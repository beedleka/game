#include "color.h"

HSV rgb_to_hsv(RGB rgb){
	f32 rgb_max = max(rgb.r, max(rgb.g, rgb.b));
	f32 rgb_min = min(rgb.r, min(rgb.g, rgb.b));
	f32 chroma = rgb_max-rgb_min;

	f32 hue = -1;
	if(chroma == 0){
		hue = 0;
	}
	else if(rgb_max == rgb.r){
		f32 segment = (rgb.g-rgb.b)/chroma;
		f32 shift = 0;
		if(segment < 0){
			shift = (float)360/60;
		}
		hue = segment+shift;
	}
	else if(rgb_max == rgb.g){
		f32 segment = (rgb.b-rgb.r)/chroma;
		f32 shift = (float)120/60;
		hue = segment+shift;
	}
	else if(rgb_max == rgb.b){
		f32 segment = (rgb.r-rgb.g)/chroma;
		f32 shift = (float)240/60;
		hue = segment+shift;
	}
	assert(hue != -1);
	return (HSV){hue*60, rgb_max > 0 ? chroma/rgb_max : 0, rgb_max};
}

RGB hsv_to_rgb(HSV hsv){
	f32 c = hsv.v*hsv.s;
	f32 x = c*(1-fabs(fmod(hsv.h/60, 2)-1));
	f32 m = hsv.v-c;
	RGB rgb_;
	if(hsv.h >= 0 && hsv.h < 60) rgb_ = (RGB){c, x, 0};
	if(hsv.h >= 60 && hsv.h < 120) rgb_ = (RGB){x, c, 0};
	if(hsv.h >= 120 && hsv.h < 180) rgb_ = (RGB){0, c, x};
	if(hsv.h >= 180 && hsv.h < 240) rgb_ = (RGB){0, x, c};
	if(hsv.h >= 240 && hsv.h < 300) rgb_ = (RGB){x, 0, c};
	if(hsv.h >= 300 && hsv.h < 360) rgb_ = (RGB){c, 0, x};
	return (RGB){
		(rgb_.r+m),
		(rgb_.g+m),
		(rgb_.b+m)
	};
}