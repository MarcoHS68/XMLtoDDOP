// XMLtoDDOP.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "XMLtoDDOP.h"

using namespace std;

static uint8_t  l_Debug, l_Comment;
static uint8_t  l_MasPars;
static char     l_Buffer[255];

struct u_regddop	gu_RegDDOP;

const char  tbl_Errors[O_Err_END][50] = {
    "No Errors",
    "Empty String",         // O_Err_EmptyString
    "Token not found",      // O_Err_NoKey
    "Invalid Tag",          // O_Err_InvalidTag
    "Missing brackets",     // O_Err_MissingBrackets
    "DOR tag overflow",     // O_Err_DOR_Overflow
};

// -----------------------
// Interpreta dati tag DVC
e_errors    fnc_Token_DVC(ofstream* File)
{
    uint16_t    l_val;

    if (l_Debug == 2)
        *File << "\t//[-- TOKEN DVC --]\n";

    // Token DVC
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X,\t// DVC\n", 'D', 'V', 'C');
    *File << l_Buffer;

    // Object ID
    l_val = gu_RegDDOP.ObjectID++;
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// ObjectID: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Device Designator
    l_val = (uint16_t)strlen(gu_RegDDOP.XML_Line.tag_B);
    if (l_val > 128) {
        std::cout << "\nError: DVC - Tag B: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "\t0x%02X,\n", l_val);
    *File << l_Buffer;

    if (l_val) {
        l_Buffer[0] = '\t';
        l_Buffer[1] = 0;
        for (uint8_t l_loop = 0; l_loop < l_val; l_loop++) {
            sprintf_s(&l_Buffer[strlen(l_Buffer)], sizeof(l_Buffer), "0x%02X, ", (uint8_t)gu_RegDDOP.XML_Line.tag_B[l_loop]);
        }
        *File << l_Buffer << "\t// Device Designator: " << gu_RegDDOP.XML_Line.tag_B << "\n";
    }

    // Software Version
    l_val = (uint16_t)strlen(gu_RegDDOP.XML_Line.tag_C);
    if (l_val > 128) {
        std::cout << "\nError: DVC - Tag C: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "\t0x%02X,\n", l_val);
    *File << l_Buffer;

    if (l_val) {
        l_Buffer[0] = '\t';
        l_Buffer[1] = 0;
        for (uint8_t l_loop = 0; l_loop < l_val; l_loop++) {
            sprintf_s(&l_Buffer[strlen(l_Buffer)], sizeof(l_Buffer), "0x%02X, ", (uint8_t)gu_RegDDOP.XML_Line.tag_C[l_loop]);
        }
        *File << l_Buffer << "\t// Software Version: " << gu_RegDDOP.XML_Line.tag_C << "\n";
    }

    //                             111111111122222222223333333333444444
    // NAME              0123456789012345678901234567890123456789012345
    if (strlen(gu_RegDDOP.XML_Line.tag_D) > 16) {
        std::cout << "\nError: DVC - Tag D: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--,");
    l_Buffer[2] = gu_RegDDOP.XML_Line.tag_D[14];
    l_Buffer[3] = gu_RegDDOP.XML_Line.tag_D[15];
    l_Buffer[8] = gu_RegDDOP.XML_Line.tag_D[12];
    l_Buffer[9] = gu_RegDDOP.XML_Line.tag_D[13];
    l_Buffer[14] = gu_RegDDOP.XML_Line.tag_D[10];
    l_Buffer[15] = gu_RegDDOP.XML_Line.tag_D[11];
    l_Buffer[20] = gu_RegDDOP.XML_Line.tag_D[8];
    l_Buffer[21] = gu_RegDDOP.XML_Line.tag_D[9];
    l_Buffer[26] = gu_RegDDOP.XML_Line.tag_D[6];
    l_Buffer[27] = gu_RegDDOP.XML_Line.tag_D[7];
    l_Buffer[32] = gu_RegDDOP.XML_Line.tag_D[4];
    l_Buffer[33] = gu_RegDDOP.XML_Line.tag_D[5];
    l_Buffer[38] = gu_RegDDOP.XML_Line.tag_D[2];
    l_Buffer[39] = gu_RegDDOP.XML_Line.tag_D[3];
    l_Buffer[44] = gu_RegDDOP.XML_Line.tag_D[0];
    l_Buffer[45] = gu_RegDDOP.XML_Line.tag_D[1];
    *File << "\t" << l_Buffer << "\t// NAME\n";

    // Serial Number
    l_val = (uint16_t)strlen(gu_RegDDOP.XML_Line.tag_E);
    if (l_val > 128) {
        std::cout << "\nError: DVC - Tag E: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "\t0x%02X,\n", l_val);
    *File << l_Buffer;

    if (l_val) {
        l_Buffer[0] = '\t';
        l_Buffer[1] = 0;
        for (uint8_t l_loop = 0; l_loop < l_val; l_loop++) {
            sprintf_s(&l_Buffer[strlen(l_Buffer)], sizeof(l_Buffer), "0x%02X, ", (uint8_t)gu_RegDDOP.XML_Line.tag_E[l_loop]);
        }
        *File << l_Buffer << "\t// Serial Number: " << gu_RegDDOP.XML_Line.tag_E << "\n";
    }

    //                             111111111122222222223333333333
    // Structure Label   0123456789012345678901234567890123456789
    if (strlen(gu_RegDDOP.XML_Line.tag_F) > 14) {
        std::cout << "\nError: DVC - Tag F: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--,");
    l_Buffer[2] = gu_RegDDOP.XML_Line.tag_F[0];
    l_Buffer[3] = gu_RegDDOP.XML_Line.tag_F[1];
    l_Buffer[8] = gu_RegDDOP.XML_Line.tag_F[2];
    l_Buffer[9] = gu_RegDDOP.XML_Line.tag_F[3];
    l_Buffer[14] = gu_RegDDOP.XML_Line.tag_F[4];
    l_Buffer[15] = gu_RegDDOP.XML_Line.tag_F[5];
    l_Buffer[20] = gu_RegDDOP.XML_Line.tag_F[6];
    l_Buffer[21] = gu_RegDDOP.XML_Line.tag_F[7];
    l_Buffer[26] = gu_RegDDOP.XML_Line.tag_F[8];
    l_Buffer[27] = gu_RegDDOP.XML_Line.tag_F[9];
    l_Buffer[32] = gu_RegDDOP.XML_Line.tag_F[10];
    l_Buffer[33] = gu_RegDDOP.XML_Line.tag_F[11];
    l_Buffer[38] = gu_RegDDOP.XML_Line.tag_F[12];
    l_Buffer[39] = gu_RegDDOP.XML_Line.tag_F[13];
    *File << "\t" << l_Buffer << "\t// Device Structure Label\n";

    //                             111111111122222222223333333333
    // Local. Label      0123456789012345678901234567890123456789
    if (strlen(gu_RegDDOP.XML_Line.tag_G) > 14) {
        std::cout << "\nError: DVC - Tag G: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--,");
    l_Buffer[2] = gu_RegDDOP.XML_Line.tag_G[12];
    l_Buffer[3] = gu_RegDDOP.XML_Line.tag_G[13];
    l_Buffer[8] = gu_RegDDOP.XML_Line.tag_G[10];
    l_Buffer[9] = gu_RegDDOP.XML_Line.tag_G[11];
    l_Buffer[14] = gu_RegDDOP.XML_Line.tag_G[8];
    l_Buffer[15] = gu_RegDDOP.XML_Line.tag_G[9];
    l_Buffer[20] = gu_RegDDOP.XML_Line.tag_G[6];
    l_Buffer[21] = gu_RegDDOP.XML_Line.tag_G[7];
    l_Buffer[26] = gu_RegDDOP.XML_Line.tag_G[4];
    l_Buffer[27] = gu_RegDDOP.XML_Line.tag_G[5];
    l_Buffer[32] = gu_RegDDOP.XML_Line.tag_G[2];
    l_Buffer[33] = gu_RegDDOP.XML_Line.tag_G[3];
    l_Buffer[38] = gu_RegDDOP.XML_Line.tag_G[0];
    l_Buffer[39] = gu_RegDDOP.XML_Line.tag_G[1];
    *File << "\t" << l_Buffer << "\t// Device Localization Label\n";

    // Extended Structure Label (lasciato a 0)
    sprintf_s(l_Buffer, "\t0x00,\t// Extended Structure Label\n\n");
    *File << l_Buffer;
    
    return O_NoErr;
}

// -----------------------
// Interpreta dati tag DET
e_errors    fnc_Token_DET(ofstream* File)
{
    uint16_t    l_val;

    if (l_Debug == 2)
        *File << "\t//[-- TOKEN DET --]\n";

    // Token DET
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X,\t// DET\n", 'D', 'E', 'T');
    *File << l_Buffer;

    // Object ID
    l_val = gu_RegDDOP.ObjectID++;
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// ObjectID: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Device Element Type
    l_val = gu_RegDDOP.XML_Line.tag_B[0] & 0xf;
    sprintf_s(l_Buffer, "\t0x%02X,\t// Device Element Type: %01d\n", (uint8_t)l_val, (uint8_t)l_val);
    *File << l_Buffer;

    // Designator
    l_val = (uint16_t)strlen(gu_RegDDOP.XML_Line.tag_D);
    if (l_val > 128) {
        std::cout << "\nError: DET - Tag D: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "\t0x%02X,\n", l_val);
    *File << l_Buffer;

    if (l_val) {
        l_Buffer[0] = '\t';
        l_Buffer[1] = 0;
        for (uint8_t l_loop = 0; l_loop < l_val; l_loop++) {
            sprintf_s(&l_Buffer[strlen(l_Buffer)], sizeof(l_Buffer), "0x%02X, ", (uint8_t)gu_RegDDOP.XML_Line.tag_D[l_loop]);
        }
        *File << l_Buffer << "\t// " << gu_RegDDOP.XML_Line.tag_D << "\n";
    }

    // Device Element Number
    l_val = atoi(gu_RegDDOP.XML_Line.tag_E);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Device Element Number: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Parent Object ID
    l_val = atoi(gu_RegDDOP.XML_Line.tag_F);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Parent Object ID: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Azzera elementi DOR
    gu_RegDDOP.DOR_Elements = 0;

    return O_NoErr;
}

// ------------------
// Chiusura token DET
// Scrive i dati DOR
e_errors    fnc_Token_CloseDET(ofstream* File)
{
    uint16_t    l_val;

    // Num Objects
    l_val = gu_RegDDOP.DOR_Elements;
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Num Objects: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Objects
    for (uint16_t l_loop = 0; l_loop < gu_RegDDOP.DOR_Elements; l_loop++) {
        l_val = gu_RegDDOP.XML_DOR[l_loop].tag_A_DevObjectID;
        sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Obj %d: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_loop+1, l_val);
        *File << l_Buffer;
    }
    *File << "\n";
    if (l_Debug == 2)
        *File << "\t//[-- CLOSE DET --]\n";

    return O_NoErr;
}

// -----------------------
// Interpreta dati tag DOR
e_errors    fnc_Token_DOR(ofstream* File)
{
    uint16_t    l_val;

    if (l_Debug == 2)
        *File << "\t//[-- TOKEN DOR --]\n";

    l_val = atoi(gu_RegDDOP.XML_Line.tag_A);
    gu_RegDDOP.XML_DOR[gu_RegDDOP.DOR_Elements].tag_A_DevObjectID = l_val;
    if (++gu_RegDDOP.DOR_Elements >= O_DOR_MaxElements) {
        *File << "\t// [Error: DOR Elements Overflow]\n";
        return O_Err_DOR_Overflow;
    }

    return O_NoErr;
}

// -----------------------
// Interpreta dati tag DPD
e_errors    fnc_Token_DPD(ofstream* File)
{
    uint16_t    l_val;

    if (l_Debug == 2)
        *File << "\t//[-- TOKEN DPD --]\n";

    // Token DPD
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X,\t// DPD\n", 'D', 'P', 'D');
    *File << l_Buffer;

    // Object ID
    l_val = atoi(gu_RegDDOP.XML_Line.tag_A);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Object ID: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Process Data DDI (hex)
    if (!strncmp(gu_RegDDOP.XML_Line.tag_B, "0x", 2)) {
        // Valore esadecimale
        l_val = (uint16_t)strtol(&gu_RegDDOP.XML_Line.tag_B[2], (char**)NULL, 16);
    } else {
        // Valore decimale
        l_val = atoi(gu_RegDDOP.XML_Line.tag_B);
    }
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Process Data DDI: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Process Data Properties
    l_val = atoi(gu_RegDDOP.XML_Line.tag_C);
    sprintf_s(l_Buffer, "\t0x%02X,\t// Process Data Properties: %d\n", (uint8_t)l_val, l_val);
    *File << l_Buffer;

    // Process Data Trigger
    l_val = atoi(gu_RegDDOP.XML_Line.tag_D);
    sprintf_s(l_Buffer, "\t0x%02X,\t// Process Data Trigger: %d\n", (uint8_t)l_val, l_val);
    *File << l_Buffer;

    // Designator
    l_val = (uint16_t)strlen(gu_RegDDOP.XML_Line.tag_E);
    if (l_val > 128) {
        std::cout << "\nError: DPD - Tag E: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "\t0x%02X,\n", l_val);
    *File << l_Buffer;

    if (l_val) {
        l_Buffer[0] = '\t';
        l_Buffer[1] = 0;
        for (uint8_t l_loop = 0; l_loop < l_val; l_loop++) {
            sprintf_s(&l_Buffer[strlen(l_Buffer)], sizeof(l_Buffer), "0x%02X, ", (uint8_t)gu_RegDDOP.XML_Line.tag_E[l_loop]);
        }
        *File << l_Buffer << "\t// " << gu_RegDDOP.XML_Line.tag_E << "\n";
    }

    // Device Value Object ID
    l_val = atoi(gu_RegDDOP.XML_Line.tag_F);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Device Value Object ID: %d\n\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    return O_NoErr;
}

// -----------------------
// Interpreta dati tag DPT
e_errors    fnc_Token_DPT(ofstream* File)
{
    uint16_t    l_val;
    uint32_t    l_val32;

    if (l_Debug == 2)
        *File << "\t//[-- TOKEN DPT --]\n";

    // Token DPT
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X,\t// DPT\n", 'D', 'P', 'T');
    *File << l_Buffer;

    // Object ID
    l_val = atoi(gu_RegDDOP.XML_Line.tag_A);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Object ID: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Process Data DDI
    l_val = atoi(gu_RegDDOP.XML_Line.tag_B);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Process Data DDI: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Property Value
    l_val32 = atol(gu_RegDDOP.XML_Line.tag_C);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X, 0x%02X,\t// Property Value: %d\n", (uint8_t)l_val32, (uint8_t)(l_val32 / 0x100), (uint8_t)(l_val32 / 0x10000), (uint8_t)(l_val32 / 0x1000000), (int32_t)l_val32);
    *File << l_Buffer;

    // Designator
    l_val = (uint16_t)strlen(gu_RegDDOP.XML_Line.tag_D);
    if (l_val > 128) {
        std::cout << "\nError: DPT - Tag D: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "\t0x%02X,\n", l_val);
    *File << l_Buffer;

    if (l_val) {
        l_Buffer[0] = '\t';
        l_Buffer[1] = 0;
        for (uint8_t l_loop = 0; l_loop < l_val; l_loop++) {
            sprintf_s(&l_Buffer[strlen(l_Buffer)], sizeof(l_Buffer), "0x%02X, ", (uint8_t)gu_RegDDOP.XML_Line.tag_D[l_loop]);
        }
        *File << l_Buffer << "\t// " << gu_RegDDOP.XML_Line.tag_D << "\n";
    }

    // Device Value Object ID
    l_val = atoi(gu_RegDDOP.XML_Line.tag_E);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Device Value Object ID: %d\n\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    return O_NoErr;
}

// -----------------------
// Interpreta dati tag DVP
e_errors    fnc_Token_DVP(ofstream* File)
{
    uint16_t    l_val;
    uint32_t    l_val32;
    float_t     f_val;

    if (l_Debug == 2)
        *File << "\t//[-- TOKEN DVP --]\n";

    // Token DVP
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X,\t// DVP\n", 'D', 'V', 'P');
    *File << l_Buffer;

    // Object ID
    l_val = atoi(gu_RegDDOP.XML_Line.tag_A);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X,\t// Object ID: %d\n", (uint8_t)l_val, (uint8_t)(l_val / 0x100), l_val);
    *File << l_Buffer;

    // Offset
    l_val32 = atol(gu_RegDDOP.XML_Line.tag_B);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X, 0x%02X,\t// Offset: %d\n", (uint8_t)l_val32, (uint8_t)(l_val32 / 0x100), (uint8_t)(l_val32 / 0x10000), (uint8_t)(l_val32 / 0x1000000), (int32_t)l_val32);
    *File << l_Buffer;

    // Scale
    f_val = atof(gu_RegDDOP.XML_Line.tag_C);
    memcpy_s((uint8_t*)&l_val32, 4, (uint8_t*)&f_val, 4);
    //l_val32 = (uint32_t)((int32_t)f_val);
    sprintf_s(l_Buffer, "\t0x%02X, 0x%02X, 0x%02X, 0x%02X,\t// Scale: %f\n", (uint8_t)l_val32, (uint8_t)(l_val32 / 0x100), (uint8_t)(l_val32 / 0x10000), (uint8_t)(l_val32 / 0x1000000), f_val);
    *File << l_Buffer;

    // Decimals
    l_val = atoi(gu_RegDDOP.XML_Line.tag_D);
    sprintf_s(l_Buffer, "\t0x%02X,\t// Decimals: %d\n", (uint8_t)l_val, l_val);
    *File << l_Buffer;

    // Designator
    l_val = (uint16_t)strlen(gu_RegDDOP.XML_Line.tag_E);
    if (l_val > 128) {
        std::cout << "\nError: DVP - Tag E: String too long\n";
        return (O_Err_InvalidTag);
    }
    sprintf_s(l_Buffer, "\t0x%02X,\n", l_val);
    *File << l_Buffer;

    if (l_val) {
        l_Buffer[0] = '\t';
        l_Buffer[1] = 0;
        for (uint8_t l_loop = 0; l_loop < l_val; l_loop++) {
            sprintf_s(&l_Buffer[strlen(l_Buffer)], sizeof(l_Buffer), "0x%02X, ", (uint8_t)gu_RegDDOP.XML_Line.tag_E[l_loop]);
        }
        *File << l_Buffer << "\t// " << gu_RegDDOP.XML_Line.tag_E << "\n\n";
    } else {
        *File << "\n";
    }

    return O_NoErr;
}

// --------------------------
// Esegue il parsing del file
e_errors    fnc_Parsing(string line, ofstream *file)
{
    static char l_indbuf, l_buf[150], l_token[10], l_tokenID, l_tag, l_tokenClose;
    char        l_chr;
    uint32_t    l_len, l_ind;
    e_errors    l_err;
    char*       p_tag;

    l_err = O_NoErr;
    l_len = line.length();
    if (!l_len)
        return O_NoErr;
        //return O_Err_EmptyString;
    l_ind = 0;
    do {
        l_chr = line.at(l_ind++);
        switch (l_MasPars) {
        case 0: // Attesa '<'
            if (l_chr == '<') {
                l_tokenClose = 0;
                l_indbuf = 0;
                l_MasPars++;
            }
            break;
        case 1: // Attende spazio per chiave
            if (l_chr == ' ') {
                l_buf[l_indbuf] = 0;
                l_MasPars++;
            } else if (l_chr < ' ') {
                break;
            } else if (l_chr == '>') {
                // Token di chiusura
                if (l_buf[0] == '/') {
                    // Si, chiusura
                    l_tokenClose++;
                    l_MasPars++;
                }
            } else {
                if (l_indbuf < sizeof(l_buf))
                    l_buf[l_indbuf++] = l_chr;
                break;
            }
            // Qui manca il break: non è un baco
        case 2: // Verifica chiave
            l_Comment = 0;
            if (strstr(l_buf, "DVC")) {
                l_tokenID = O_Token_DVC;
                if (l_tokenClose) {
                    if (l_Debug == 2)
                        *file << "\t// DVC Close\n";
                    l_MasPars = 0;
                    break;
                }
                l_MasPars = 10;
            }
            else if (strstr(l_buf, "DET")) {
                l_tokenID = O_Token_DET;
                if (l_tokenClose) {
                    if (l_Debug == 2)
                        *file << "\t// DET Close\n";
                    fnc_Token_CloseDET(file);
                    gu_RegDDOP.DET_Level = 0;
                    l_MasPars = 0;
                    break;
                }
                l_MasPars = 10;
            }
            else if (strstr(l_buf, "DPD")) {
                l_tokenID = O_Token_DPD;
                if (l_tokenClose) {
                    if (l_Debug == 2)
                        *file << "\t// DPD Close\n";
                    l_MasPars = 0;
                    break;
                }
                l_MasPars = 10;
            }
            else if (strstr(l_buf, "DPT")) {
                l_tokenID = O_Token_DPT;
                if (l_tokenClose) {
                    if (l_Debug == 2)
                        *file << "\t// DPT Close\n";
                    l_MasPars = 0;
                    break;
                }
                l_MasPars = 10;
            }
            else if (strstr(l_buf, "DVP")) {
                l_tokenID = O_Token_DVP;
                if (l_tokenClose) {
                    if (l_Debug == 2)
                        *file << "\t// DVP Close\n";
                    l_MasPars = 0;
                    break;
                }
                l_MasPars = 10;
            }
            else if (strstr(l_buf, "DOR")) {
                l_tokenID = O_Token_DOR;
                if (l_tokenClose) {
                    if (l_Debug == 2)
                        *file << "\t// DOR Close\n";
                    l_MasPars = 0;
                    break;
                }
                l_MasPars = 10;
            }
            else if (strstr(l_buf, "?xml")) {
                // Chiave XML: ignora senza segnalare warning
                l_MasPars = 0;
                break;
            }
            else if (strstr(l_buf, "!--")) {
                // Chiave commento
                // Deve attendere chiusura -->
                l_Comment = 1;
                l_MasPars = 40;
                break;
            }
            else {
                // Chiave non trovata: riparte da capo
                l_MasPars = 0;
                *file << "\n// " << line << "\n";
                *file << "// Warning: Invalid Token?\n\n";
                break;
                //return O_Err_NoKey;
            }
            memset(&gu_RegDDOP.XML_Line, 0, sizeof(gu_RegDDOP.XML_Line));
            gu_RegDDOP.XML_Line.tokenID = l_tokenID;
            strcpy_s(gu_RegDDOP.XML_Line.tag_Token, 10, l_buf);   // Copia il token nel buffer linea
            l_tag = 0;
            l_indbuf = 0;
            break;
        case 10:    // Attende tag cercando '='
            if (l_chr <= ' ')
                break;
            if (l_chr == '/') {
                // Chiusura totale token
                l_MasPars = 30;
                break;
            }
            if (l_chr == '>') {
                // Chiusura parziale token
                l_MasPars = 20;
                break;
            }
            if (l_chr == '=') {
                // Trovato '='
                if (!l_indbuf || l_indbuf > 1) {
                    // Errore tag
                    l_MasPars = 0;
                    return O_Err_InvalidTag;
                }
                l_tag = l_buf[0];   // Salva il tag rilevato
                l_MasPars++;
                break;
            }
            if (l_indbuf < sizeof(l_buf))
                l_buf[l_indbuf++] = l_chr;
            break;
        case 11:    // Attende apici apertura
            if (l_chr <= ' ')
                break;
            if (l_chr == '"') {
                l_indbuf = 0;
                l_MasPars++;
            }
            else {
                // Altri caratteri: errore
                l_MasPars = 0;
                return O_Err_MissingBrackets;
            }
            break;
        case 12:    // Attende apici chiusura
            if (l_chr == '"') {
                switch (l_tag) {
                case 'A':
                    p_tag = gu_RegDDOP.XML_Line.tag_A;
                    break;
                case 'B':
                    p_tag = gu_RegDDOP.XML_Line.tag_B;
                    break;
                case 'C':
                    p_tag = gu_RegDDOP.XML_Line.tag_C;
                    break;
                case 'D':
                    p_tag = gu_RegDDOP.XML_Line.tag_D;
                    break;
                case 'E':
                    p_tag = gu_RegDDOP.XML_Line.tag_E;
                    break;
                case 'F':
                    p_tag = gu_RegDDOP.XML_Line.tag_F;
                    break;
                case 'G':
                    p_tag = gu_RegDDOP.XML_Line.tag_G;
                    break;
                default:
                    l_MasPars = 0;
                    return O_Err_InvalidTag;
                }
                l_buf[l_indbuf] = 0;
                strcpy_s(p_tag, 128, l_buf);
                l_indbuf = 0;
                l_MasPars = 10;
                break;
            }
            if (l_indbuf < sizeof(l_buf))
                l_buf[l_indbuf++] = l_chr;
            break;
        case 20:    // Chiusura parziale token '>'
            switch (gu_RegDDOP.XML_Line.tokenID) {
            case O_Token_DVC:
                gu_RegDDOP.DET_Level = 0;
                l_err = fnc_Token_DVC(file);
                break;
            case O_Token_DET:
                gu_RegDDOP.DET_Level++;
                l_err = fnc_Token_DET(file);
                break;
            case O_Token_DOR:
                l_err = fnc_Token_DOR(file);
                break;
            case O_Token_DPD:
                l_err = fnc_Token_DPD(file);
                break;
            case O_Token_DPT:
                l_err = fnc_Token_DPT(file);
                break;
            case O_Token_DVP:
                l_err = fnc_Token_DVP(file);
                break;
            default:
                l_err = O_Err_InvalidTag;
            }
            if (l_err != O_NoErr)
                return l_err;
            // Nessun errore: riparte alla ricerca dei token
            l_indbuf = 0;
            l_MasPars = 0;
            break;
        case 30:    // Chiusura totale token '/': deve attendere '>'
            if (l_chr != '>') {
                // ERRORE
                l_indbuf = 0;
                l_MasPars = 0;
                return O_Err_MissingBrackets;
            }
            l_MasPars = 20;
            break;
        case 40:    // Attende chiusura commento '-->'
            if (l_chr == '-')
                l_MasPars++;
            break;
        case 41:
            if (l_chr == '-')
                l_MasPars++;
            else
                l_MasPars = 40;
            break;
        case 42:
            if (l_chr == '>') {
                l_indbuf = 0;
                l_MasPars = 0;
            }
            else {
                l_MasPars = 40;
            }
            break;
        }
    } while (--l_len);

    return l_err;
}

// ---------------
// Visualizza Help
void    fnc_Help(void)
{
    std::cout << "\nXMLtoDDOP HELP";
    std::cout << "\nXMLtoDDOP [opt] <Source XML> <Destination C File>";
    std::cout << "\nExample: XMLtoDDOP ddop.xml ddop.c";
    std::cout << "\n         XMLtoDDOP -d ddop.xml ddop.c = Add XML rows as comments";
    std::cout << "\nWarning: Tag B of DPD key is express in decimal. If you want to express it in hex, please add '0x' before number\n";
    std::cout << "\n-d or -d0 = Debug Mode with only the XML lines added into C file as comments";
    std::cout << "\n-d1       = Debug Mode with all informations added into C file as comments";
    std::cout << "\n-h = Help";
    std::cout << "\n-c = Credits\n";
}

// ----------------------------
// Programma principale
// Estrae riga di comando
// Esegue parsing e conversione
int main(int argc, char *argv[])
{
    char* xmlF, * cF;
    char xDef[20] = "ddop.xml";
    char cDef[20] = "ddop.c";

    l_Debug = 0;
    l_Comment = 0;

    switch (argc) {
    case 2:
        if (!strcmp(argv[1], "-h")) {
            // Help
            fnc_Help();
            return 0;
        } else if (!strcmp(argv[1], "-c")) {
            // Credits
            std::cout << "\nXMLtoDDOP";
            std::cout << "\nConvert XML ISOBUS DDOP file into C File";
            std::cout << "\nWritten by: Marco Di Biaggio";
            std::cout << "\n(C)2025 Agricolmeccanica srl";
            std::cout << "\n        UDINE - Italy\n";
            return 0;
        }
        xmlF = argv[1];
        cF = cDef;
        break;
    case 3:
        if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "-d0")) {
            l_Debug = 1;    // Debug completo
            xmlF = argv[2];
            cF = cDef;
        } else if (!strcmp(argv[1], "-d1")) {
            l_Debug = 2;    // Debug parziale (solo righe xml)
            xmlF = argv[2];
            cF = cDef;
        } else if (!strcmp(argv[1], "-h")) {
            // Help
            fnc_Help();
            return 0;
        } else {
            xmlF = argv[1];
            cF = argv[2];
        }
        break;
    case 4:
        // Parametri
        if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "-d0"))
            l_Debug = 1;
        else if (!strcmp(argv[1], "-d1"))
            l_Debug = 2;
        else if (!strcmp(argv[1], "-h")) {
            // Help
            fnc_Help();
            return 0;
        }
        xmlF = argv[2];
        cF = argv[3];
        break;
    default:
        std::cout << "\nError: No input file\n";
        return 1;
    }

    ifstream    xmlFile(xmlF);
    ofstream    cFile(cF);

    if (!xmlFile.is_open()) {
        cerr << "Errore nell'apertura del file XML o file non trovato." << endl;
        cFile.close();
        return 1;
    }

    cFile << "#include <stdint.h>\n";
    cFile << "#include <stdio.h>\n\n";
    cFile << "const uint8_t DDOP_E2IS[] =\n{\n";

    // Inizializza variabili importanti
    gu_RegDDOP.ObjectID = 0;
    l_MasPars = 0;

    // Esegue il parsing del file XML e lo converte in codice C
    string line;
    e_errors l_err;
    while (getline(xmlFile, line)) {
        if ((l_err = fnc_Parsing(line, &cFile)) != O_NoErr) {
            cFile << "\n//" << line << "\n";
            cFile << "// ERROR N." << l_err << " " << tbl_Errors[l_err] << "\n\n";
            break;
        }
        if (l_Debug || l_Comment)
            cFile << "//" << line << "\n";
    }

    cFile << "};\n\n";
    cFile << "const size_t DDOP_E2IS_len = sizeof(DDOP_E2IS);\n" << endl;

    xmlFile.close();
    cFile.close();

    if (l_err != O_NoErr)
        cout << "Conversione conclusa con Errori. Vedere file generato." << endl;
    else
        cout << "Conversione completata. File [" << cF << "] generato." << endl;
    return 0;
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
