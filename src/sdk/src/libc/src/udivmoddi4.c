
 

typedef int SItype __attribute__(( mode( SI ) ));
typedef unsigned int USItype __attribute__(( mode( SI ) ));
typedef int DItype __attribute__(( mode( DI ) ));
typedef unsigned int UDItype __attribute__(( mode( DI ) ));

#define Wtype SItype
#define UWtype USItype
#define DWtype DItype
#define UDWtype UDItype

#define W_TYPE_SIZE 32

struct DWstruct {
    Wtype low;
    Wtype high;
};

typedef union {
    struct DWstruct s;
    DWtype ll;
} DWunion;

#define udiv_qrnnd(q, r, n1, n0, dv) \
    __asm__("div{l} %4" \
        : "=a" ((USItype) (q)), "=d" ((USItype) (r)) \
        : "0" ((USItype) (n0)), "1" ((USItype) (n1)), "rm" ((USItype) (dv)))

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    __asm__("sub{l} {%5,%1|%1,%5}\n\tsbb{l} {%3,%0|%0,%3}" \
        : "=r" ((USItype) (sh)), "=&r" ((USItype) (sl)) \
        : "0" ((USItype) (ah)), "g" ((USItype) (bh)), \
          "1" ((USItype) (al)), "g" ((USItype) (bl)))

#define umul_ppmm(w1, w0, u, v) \
    __asm__("mul{l} %3" \
        : "=a" ((USItype) (w0)), "=d" ((USItype) (w1)) \
        : "%0" ((USItype) (u)), "rm" ((USItype) (v)))

#define count_leading_zeros(count, x)   ((count) = __builtin_clz (x))

static inline __attribute__(( __always_inline__ ))
UDWtype __udivmoddi4( UDWtype n, UDWtype d, UDWtype* rp ) {
    const DWunion nn = {.ll = n};
    const DWunion dd = {.ll = d};
    DWunion rr;
    UWtype d0, d1, n0, n1, n2;
    UWtype q0, q1;
    UWtype b, bm;

    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if ( d1 == 0 ) {
        if ( d0 > n1 ) {
            /* 0q = nn / 0D */

            udiv_qrnnd (q0, n0, n1, n0, d0);
            q1 = 0;

            /* Remainder in n0.  */
        } else {
            /* qq = NN / 0d */

            if (d0 == 0)
                d0 = 1 / d0;    /* Divide intentionally by zero.  */

            udiv_qrnnd (q1, n1, 0, n1, d0);
            udiv_qrnnd (q0, n0, n1, n0, d0);

            /* Remainder in n0.  */
        }

        if (rp != 0) {
            rr.s.low = n0;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if ( d1 > n1 )  {
            /* 00 = nn / DD */

            q0 = 0;
            q1 = 0;

            /* Remainder in n1n0.  */
            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            /* 0q = NN / dd */

            count_leading_zeros (bm, d1);

            if (bm == 0) {
                /* From (n1 >= d1) /\ (the most significant bit of d1 is set),
                  conclude (the most significant bit of n1 is set) /\ (the
                  quotient digit q0 = 0 or 1).

                This special case is necessary, not an optimization.  */

                /* The condition on the next line takes advantage of that
                  n1 >= d1 (true due to program flow).  */
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss (n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;

                q1 = 0;

                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                UWtype m1, m0;
                /* Normalize.  */

                b = W_TYPE_SIZE - bm;

                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd (q0, n1, n2, n1, d1);
                umul_ppmm (m1, m0, q0, d0);

                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss (m1, m0, m1, m0, d1, d0);
                }

                q1 = 0;

                /* Remainder in (n1n0 - m1m0) >> bm.  */
                if (rp != 0) {
                    sub_ddmmss (n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    const DWunion ww = {{.low = q0, .high = q1}};

    return ww.ll;
}

DWtype __moddi3( DWtype u, DWtype v ) {
  Wtype c = 0;
  DWunion uu = {.ll = u};
  DWunion vv = {.ll = v};
  DWtype w;

  if ( uu.s.high < 0 )
    c = ~c,
    uu.ll = -uu.ll;

  if ( vv.s.high < 0 )
    vv.ll = -vv.ll;

  ( void )__udivmoddi4( uu.ll, vv.ll, ( UDWtype* )&w );

  if ( c )
    w = -w;

  return w;
}

UDWtype __umoddi3( UDWtype u, UDWtype v ) {
    UDWtype w;

    ( void )__udivmoddi4( u, v, &w );

    return w;
}

DWtype __divdi3( DWtype u, DWtype v ) {
  Wtype c = 0;
  DWunion uu = {.ll = u};
  DWunion vv = {.ll = v};
  DWtype w;

  if (uu.s.high < 0)
    c = ~c,
    uu.ll = -uu.ll;

  if (vv.s.high < 0)
    c = ~c,
    vv.ll = -vv.ll;

  w = __udivmoddi4( uu.ll, vv.ll, ( UDWtype* )0 );

  if (c)
    w = -w;

  return w;
}

UDWtype __udivdi3( UDWtype n, UDWtype d ) {
    return __udivmoddi4( n, d, ( UDWtype* )0 );
}
