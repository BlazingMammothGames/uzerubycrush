// jewel shatter
const char patch00[] PROGMEM ={
0,PC_NOISE_PARAMS,1,
0,PC_ENV_VOL,0xa0,
0,PC_ENV_SPEED,-25, 
1,PC_ENV_SPEED,-15,
0,PC_NOISE_PARAMS,1,
0,PATCH_END
};

// error oop
const char patch01[] PROGMEM ={
0,PC_WAVE,0,
0,PC_PITCH,38,
0,PC_ENV_SPEED,-30,
0,PATCH_END
};

// select bip
const char patch02[] PROGMEM ={
0,PC_WAVE,0,
0,PC_PITCH,64,
0,PC_ENV_SPEED,-40,
0,PATCH_END
};

// level up
const char patch03[] PROGMEM ={
0,PC_WAVE,4,
0,PC_ENV_SPEED,-8,
0,PC_PITCH,80,
3,PC_PITCH,78,
3,PC_PITCH,84,
2,PC_PITCH,76,
2,PC_PITCH,88,
2,PC_PITCH,74,
1,PC_PITCH,92,
0,PC_ENV_SPEED,-4,
3,PC_PITCH,96,
3,PC_PITCH,90,
3,PC_PITCH,96,
3,PC_PITCH,90,
3,PC_PITCH,96,
3,PC_PITCH,90,
1,PC_NOTE_CUT,0,
0,PATCH_END 
};

/*// crash
// type = 1
const char patch01[] PROGMEM ={
0,PC_NOISE_PARAMS,1,
0,PC_ENV_VOL,0xa0,
0,PC_ENV_SPEED,-25, 
1,PC_ENV_SPEED,-4,
0,PC_NOISE_PARAMS,1,
0,PATCH_END
};

// guitar twang
// type = 1
const char patch02[] PROGMEM ={
0,PC_NOISE_PARAMS,1,
0,PC_ENV_VOL,0xa0,
0,PC_ENV_SPEED,-25, 
1,PC_ENV_SPEED,-5,
0,PC_NOISE_PARAMS,0,
0,PATCH_END
};

// "bomb"
// type = 1
const char patch03[] PROGMEM ={
0,PC_NOISE_PARAMS,1,
0,PC_ENV_VOL,0xa0,
0,PC_ENV_SPEED,-50, 
1,PC_ENV_SPEED,-2,
0,PC_NOISE_PARAMS,100,
0,PATCH_END
};

// spring
// type = 0
const char patch04[] PROGMEM ={
0,PC_WAVE,14,
0,PC_ENV_SPEED,-8,
0,PATCH_END
};*/

const struct PatchStruct patches[] PROGMEM = {
{1,NULL,patch00,0,0},
{0,NULL,patch01,0,0},
{0,NULL,patch02,0,0},
{0,NULL,patch03,0,0},
};