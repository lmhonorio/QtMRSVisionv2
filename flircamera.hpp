#pragma once

#define _AFXDLL

#include "basegigecamera.hpp"
#include "temperature.hpp"

#include "atlconv.h"

#include <QThread>


#define ASY_SAFEGUARD 1.0002
#define EXP_SAFEGUARD 709.78

typedef struct {
    BYTE r;
    BYTE g;
    BYTE b;
} RGB_T;

static RGB_T iron[128] =  {
                {0,   0,  0},
                {0,   0,  16},
                {0,   0,  36},
                {0,   0,  51},
                {0,   0,  66},
                {0,   0,  81},
                {2,   0,  90},
                {4,   0,  99},
                {7,   0, 106},
                {11,   0, 115},
                {14,   0, 119},
                {20,   0, 123},
                {27,   0, 128},
                {33,   0, 133},
                {41,   0, 137},
                {48,   0, 140},
                {55,   0, 143},
                {61,   0, 146},
                {66,   0, 149},
                {72,   0, 150},
                {78,   0, 151},
                {84,   0, 152},
                {91,   0, 153},
                {97,   0, 155},
                {104,   0, 155},
                {110,   0, 156},
                {115,   0, 157},
                {122,   0, 157},
                {128,   0, 157},
                {134,   0, 157},
                {139,   0, 157},
                {146,   0, 156},
                {152,   0, 155},
                {157,   0, 155},
                {162,   0, 155},
                {167,   0, 154},
                {171,   0, 153},
                {175,   1, 152},
                {178,   1, 151},
                {182,   2, 149},
                {185,   4, 149},
                {188,   5, 147},
                {191,   6, 146},
                {193,   8, 144},
                {195,  11, 142},
                {198,  13, 139},
                {201,  17, 135},
                {203,  20, 132},
                {206,  23, 127},
                {208,  26, 121},
                {210,  29, 116},
                {212,  33, 111},
                {214,  37, 103},
                {217,  41,  97},
                {219,  46,  89},
                {221,  49,  78},
                {223,  53,  66},
                {224,  56,  54},
                {226,  60,  42},
                {228,  64,  30},
                {229,  68,  25},
                {231,  72,  20},
                {232,  76,  16},
                {234,  78,  12},
                {235,  82,  10},
                {236,  86,   8},
                {237,  90,   7},
                {238,  93,   5},
                {239,  96,   4},
                {240, 100,   3},
                {241, 103,   3},
                {241, 106,   2},
                {242, 109,   1},
                {243, 113,   1},
                {244, 116,   0},
                {244, 120,   0},
                {245, 125,   0},
                {246, 129,   0},
                {247, 133,   0},
                {248, 136,   0},
                {248, 139,   0},
                {249, 142,   0},
                {249, 145,   0},
                {250, 149,   0},
                {251, 154,   0},
                {252, 159,   0},
                {253, 163,   0},
                {253, 168,   0},
                {253, 172,   0},
                {254, 176,   0},
                {254, 179,   0},
                {254, 184,   0},
                {254, 187,   0},
                {254, 191,   0},
                {254, 195,   0},
                {254, 199,   0},
                {254, 202,   1},
                {254, 205,   2},
                {254, 208,   5},
                {254, 212,   9},
                {254, 216,  12},
                {255, 219,  15},
                {255, 221,  23},
                {255, 224,  32},
                {255, 227,  39},
                {255, 229,  50},
                {255, 232,  63},
                {255, 235,  75},
                {255, 238,  88},
                {255, 239, 102},
                {255, 241, 116},
                {255, 242, 134},
                {255, 244, 149},
                {255, 245, 164},
                {255, 247, 179},
                {255, 248, 192},
                {255, 249, 203},
                {255, 251, 216},
                {255, 253, 228},
                {255, 254, 239},
                {255, 255, 249},
                {255, 255, 249},
                {255, 255, 249},
                {255, 255, 249},
                {255, 255, 249},
                {255, 255, 249},
                {255, 255, 249},
                {255, 255, 249}
};

static RGB_T rain[128] =  {
            {0,   0,   0},
            {0,   0,   0},
            {15,   0,  15},
            {31,   0,  31},
            {47,   0,  47},
            {63,   0,  63},
            {79,   0,  79},
            {95,   0,  95},
            {111,   0, 111},
            {127,   0, 127},
            {143,   0, 143},
            {159,   0, 159},
            {175,   0, 175},
            {191,   0, 191},
            {207,   0, 207},
            {223,   0, 223},
            {239,   0, 239},
            {255,   0, 255},
            {239,   0, 250},
            {223,   0, 245},
            {207,   0, 240},
            {191,   0, 236},
            {175,   0, 231},
            {159,   0, 226},
            {143,   0, 222},
            {127,   0, 217},
            {111,   0, 212},
            {95,   0, 208},
            {79,   0, 203},
            {63,   0, 198},
            {47,   0, 194},
            {31,   0, 189},
            {15,   0, 184},
            {0,   0, 180},
            {0,  15, 184},
            {0,  31, 189},
            {0,  47, 194},
            {0,  63, 198},
            {0,  79, 203},
            {0,  95, 208},
            {0, 111, 212},
            {0, 127, 217},
            {0, 143, 222},
            {0, 159, 226},
            {0, 175, 231},
            {0, 191, 236},
            {0, 207, 240},
            {0, 223, 245},
            {0, 239, 250},
            {0, 255, 255},
            {0, 245, 239},
            {0, 236, 223},
            {0, 227, 207},
            {0, 218, 191},
            {0, 209, 175},
            {0, 200, 159},
            {0, 191, 143},
            {0, 182, 127},
            {0, 173, 111},
            {0, 164,  95},
            {0, 155,  79},
            {0, 146,  63},
            {0, 137,  47},
            {0, 128,  31},
            {0, 119,  15},
            {0, 110,   0},
            {15, 118,   0},
            {30, 127,   0},
            {45, 135,   0},
            {60, 144,   0},
            {75, 152,   0},
            {90, 161,   0},
            {105, 169,  0},
            {120, 178,  0},
            {135, 186,  0},
            {150, 195,  0},
            {165, 203,  0},
            {180, 212,  0},
            {195, 220,  0},
            {210, 229,  0},
            {225, 237,  0},
            {240, 246,  0},
            {255, 255,  0},
            {251, 240,  0},
            {248, 225,  0},
            {245, 210,  0},
            {242, 195,  0},
            {238, 180,  0},
            {235, 165,  0},
            {232, 150,  0},
            {229, 135,  0},
            {225, 120,  0},
            {222, 105,  0},
            {219,  90,  0},
            {216,  75,  0},
            {212,  60,  0},
            {209,  45,  0},
            {206,  30,  0},
            {203,  15,  0},
            {200,   0,  0},
            {202,  11,  11},
            {205,  23,  23},
            {207,  34,  34},
            {210,  46,  46},
            {212,  57,  57},
            {215,  69,  69},
            {217,  81,  81},
            {220,  92,  92},
            {222, 104, 104},
            {225, 115, 115},
            {227, 127, 127},
            {230, 139, 139},
            {232, 150, 150},
            {235, 162, 162},
            {237, 173, 173},
            {240, 185, 185},
            {242, 197, 197},
            {245, 208, 208},
            {247, 220, 220},
            {250, 231, 231},
            {252, 243, 243},
            {252, 243, 243},
            {252, 243, 243},
            {252, 243, 243},
            {252, 243, 243},
            {252, 243, 243},
            {252, 243, 243},
            {252, 243, 243}
};

class CFlirCamera:public CBaseGIGeCamera
{


public:

    CFlirCamera(void);
    ~CFlirCamera(void);

    QMutex* mutex;

    J_STATUS_TYPE openStream(uint32_t iChannel);

    void StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo) override;

    void setHandler(CAM_HANDLE* hCam, int idepth, int ichannels);

    void HandleReceivedImage(void) override;


    CTemperature imgToTemp(long lPixval);
    CTemperature objSigToTemp(double dObjSig);

    double doCalcAtmTao(void);
    float TauToTemp(USHORT sig);
    double powToObjSig(double dPow);
    double doCalcK1(void);
    double doCalcK2(double dAmbObjSig, double dAtmObjSig, double dExtOptTempObjSig);
    void   doUpdateCalcConst(void);
    double tempToObjSig(double dblKelvin);



    //thermal camera only
    CTemperature		T;
    QString				unit;



    USHORT getSpot() { return (USHORT)m_SpotValue; }
    USHORT getCenterSpot() { return (USHORT)m_CenterSpotValue; }
    USHORT getScaleLo() { return m_ScaleLow; }
    USHORT getScaleHi() { return m_ScaleHigh; }
    USHORT getAreaAvg() { return m_AreaAvg;}
    USHORT getAreaMin() { return m_AreaMin;}
    USHORT getAreaMax() { return m_AreaMax;}


         // Tau Planck constants
    int                 m_R;
    double              m_B;
    double              m_F;
    double              m_O;
    double              m_WT;
    double              m_W4WT;
    ULONG               m_J0; // Global offset
    double              m_J1; // Global gain
    double              m_K1;
    double              m_K2;
    // Object parameters
    double              m_Emissivity;
    double              m_ObjectDistance;
    double              m_AtmTemp;
    double              m_AmbTemp;
    double              m_AtmTao;
    double              m_ExtOptTransm;
    double              m_ExtOptTemp;
    double              m_RelHum;
    // Spectral response parameters
    double              m_X;
    double              m_alpha1;
    double              m_alpha2;
    double              m_beta1;
    double              m_beta2;






private:
    //HWND* hPicBox;


    USHORT  m_AreaAvg;
    USHORT  m_AreaMin;
    USHORT  m_AreaMax;

    QPoint  m_SpotPT; // Spot position

    DWORD   m_CenterSpotValue;
    DWORD	m_SpotValue;
    USHORT  m_ScaleLow;
    USHORT  m_ScaleHigh;

};

