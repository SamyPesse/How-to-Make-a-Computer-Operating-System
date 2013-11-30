
 

#include <string.h>

#include "time_int.h"

const unsigned short int monthdays[ 13 ] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};

const unsigned short int monthdays2[ 13 ] = {
    0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366
};

const unsigned short int sumofdays[ 60 ] = {
    0, 366, 731, 1096, 1461, 1827, 2192, 2557, 2922, 3288, 3653, 4018, 4383, 4749,
    5114, 5479, 5844, 6210, 6575, 6940, 7305, 7671, 8036, 8401, 8766, 9132, 9497,
    9862, 10227, 10593, 10958, 11323, 11688, 12054, 12419, 12784, 13149, 13515,
    13880, 14245, 14610, 14976, 15341, 15706, 16071, 16437, 16802, 17167, 17532,
    17898, 18263, 18628, 18993, 19359, 19724, 20089, 20454, 20820, 21185, 21550
};

int _gmtime( time_t timeval, tm_t* ret ) {
    int i;

    ret->tm_sec = timeval % SECONDS_PER_MINUTE;
    timeval /= SECONDS_PER_MINUTE;
    ret->tm_min = timeval % MINUTES_PER_HOUR;
    timeval /= MINUTES_PER_HOUR;
    ret->tm_hour = timeval % HOURS_PER_DAY;
    timeval /= HOURS_PER_DAY;

    /* 1970(Epoch) is a leap year, and every 4th year too.
       2000 is also a leap year, because its divisible by 400.
       timeval now holds the difference of whole days.
       1 Jan 1970 was a Thursday. */

    ret->tm_wday = (4 + timeval) % 7;

    /* TODO: return NULL when year does not fit. */
    ret->tm_year = EPOCH;

    for ( i = 0; i < 60; i++ ) {
        if ( sumofdays[ i ] > timeval ) {
            ret->tm_year = EPOCH + i - 1;
            timeval -= sumofdays[ i - 1 ];

            break;
        }
    }

    ret->tm_yday = ( int )timeval;

    if ( ret->tm_year % 4 == 0 ) {
        for ( ret->tm_mon = 0; ret->tm_mon < 12; ret->tm_mon++ ) {
            if ( monthdays2[ ret->tm_mon ] > timeval ) {
                timeval -= monthdays2[ --ret->tm_mon ];
                break;
            }
        }
    } else {
        for ( ret->tm_mon = 0; ret->tm_mon < 12; ret->tm_mon++ ) {
            if ( monthdays[ ret->tm_mon ] > timeval ) {
                timeval -= monthdays[ --ret->tm_mon ];
                break;
            }
        }
    }

    ret->tm_mday = ( int )timeval + 1;
    ret->tm_isdst = -1;

    return 0;
}

int daysdiff( int year, int month, int day ) {
    int i, days = 0;

    for ( i = EPOCH; i < year; i++ ) {
        if ( i % 4 == 0 ) { /* If it is a leap year */
            days += 366;
        } else {
            days += 365;
        }
    }

    if ( year % 4 == 0 ) {
        days += monthdays2[ month ];
    } else {
        days += monthdays[ month ];
    }

    days += day - 1;

    return days;
}

int dayofweek( int year, int month, int day ) {
    /* The UNIX Epoch(1 Jan 1970) was a Thursday */
    return ( 4 + daysdiff( year, month, day ) ) % 7;
}
