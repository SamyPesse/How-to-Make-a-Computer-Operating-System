#ifndef __API_FB__
#define __API_FB__

struct fb_info{
	unsigned int		w;	//largeur
	unsigned int		h;	//hauteur
	char				bpp;	//bit per pixel
	char				state;	//etat de la carte
	unsigned int*		vmem;	//video memory
};

enum{
	FB_NOT_ACTIVE=0,
	FB_ACTIVE=1,
};

#define API_FB_IS_AVAILABLE			0x801
#define API_FB_GET_INFO				0x802	//info actuel
#define API_FB_GET_BINFO			0x803	//meilleur info
#define API_FB_SET_INFO				0x804


#endif
