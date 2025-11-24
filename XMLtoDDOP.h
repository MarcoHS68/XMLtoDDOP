#pragma once

// File header XMLtoDDOP
// Creato: Di Biaggio Marco
// Data..: 07/11/2025

// -------------------
// Costanti utilizzate
#define	O_DET_MaxObjects	200
#define	O_DOR_MaxObjects	200

// ----------------------
// Elenco numerico tokens
enum e_tokens {
	O_Token_Null = 0,
	O_Token_DVC,
	O_Token_DET,
	O_Token_DPD,
	O_Token_DPT,
	O_Token_DVP,
	O_Token_DOR,
	
	O_Token_END
};

// -------------
// Elenco errori
enum e_errors {
	O_NoErr = 0,
	O_Err_EmptyString,		// Stringa passata è vuota
	O_Err_NoKey,			// Chiave non trovata
	O_Err_InvalidTag,		// Tag non valido
	O_Err_MissingBrackets,	// Mancano apici apertura
	O_Err_DOR_Overflow,		// Overflow elementi DOR
	O_Err_DPD_Overflow,		// Overflow elementi DPD o DPT
	O_Err_DVP_Overflow,		// Overflow elementi DVP

	O_Err_END
};

// ---------------------------------------------------
// ---------------------------------------------------
// Parte Device Descriptor Objects Annex.A ISO11783-10

// ---------------------
// A.2 Device Object DVC
typedef struct u_DVC {
	uint16_t	ObjectID;

	uint8_t		DesignatorBytes;
	char		Designator[128];

	uint8_t		SoftwareBytes;
	char		SoftwareVer[128];

	uint64_t	NAME;

	uint8_t		SerialBytes;
	char		SerialNumber[128];

	char		DevStructureLabel[7];

	char		DevLocalizationLabel[7];

	uint8_t		ExtStructureBytes;
	char		ExtStructureLabel[32];
} t_uDVC, *p_uDVC;

// -----------------------------
// A.3 Device Element Object DET
typedef struct u_DET {
	uint16_t	ObjectID;

	uint8_t		DevElementType;

	uint8_t		DesignatorBytes;
	char		Designator[128];

	uint16_t	DevElementNumber;

	uint16_t	ParentObjectID;

	uint16_t	NumObjects;
	uint16_t	Objects[O_DET_MaxObjects];
} t_uDET, *p_uDET;

// ----------------------------------
// A.4 Device Process Data Object DPD
typedef struct u_DPD {
	uint16_t	ObjectID;

	uint16_t	ProcessDataDDI;

	union {
		uint8_t	all;
		struct {
			unsigned MemberOfDefaultSet : 1;
			unsigned Settable : 1;
			unsigned ControlSource : 1;
			unsigned : 5;
		} b;
	} ProcessDataProperties;

	union {
		uint8_t	all;
		struct {
			unsigned TimeInterval : 1;
			unsigned DistanceInterval : 1;
			unsigned ThresholdLimits : 1;
			unsigned OnChange : 1;
			unsigned Total : 1;
			unsigned : 3;
		} b;
	} ProcessDataTrigger;

	uint8_t		DesignatorBytes;
	char		Designator[128];

	uint16_t	DevValObjectID;
} t_uDPD, *p_uDPD;

// --------------------------
// A.5 Device Property Object
typedef struct u_DPT {
	uint16_t	ObjectID;

	uint16_t	PropertyDDI;
	int32_t		PropertyValue;

	uint8_t		DesignatorBytes;
	char		Designator[128];

	uint16_t	DevValObjectID;
} t_uDPT, *p_uDPT;

// ------------------------------------
// A.6 Device Value Presentation Object
typedef struct u_DVP {
	uint16_t	ObjectID;

	int32_t		Offset;
	float		Scale;
	uint8_t		Decimals;

	uint8_t		DesignatorBytes;
	char		Designator[128];
} t_uDVP, *p_uDVP;

// -----------------------------
// -----------------------------
// Parte XML Annex.D ISO11783-10

// ---------------
// D.19 Device DVC
typedef struct u_XML_DVC {
	char	tag_A_ID[15];
	char	tag_B_Designator[129];
	char	tag_C_SoftwareVer[129];
	char	tag_D_NAME[20];
	char	tag_E_SerialNumber[129];
	char	tag_F_DevStructureLabel[33];
	char	tag_G_DevLocalizationLabel[15];
} t_uXML_DVC, *p_uXML_DVC;

// -----------------------
// D.21 Device Element DET
typedef struct u_XML_DET {
	char		tag_A_ID[15];
	uint16_t	tag_B_ObjectID;
	uint8_t		tag_C_DevElementType;
	char		tag_D_Designator[33];
	uint16_t	tag_E_DevElementNumber;
	uint16_t	tag_F_ParentObjectID;

	uint16_t	dor_NumObjects;
	uint16_t	dor_ObjectID[O_DOR_MaxObjects];
} t_uXML_DET, *p_uXML_DET;

// ----------------------------
// D.23 Device Process Data DPD
typedef struct u_XML_DPD {
	uint16_t	tag_A_ObjectID;
	uint16_t	tag_B_ProcessDataDDI;
	union {
		uint8_t	all;
		struct {
			unsigned MemberOfDefaultSet : 1;
			unsigned Settable : 1;
			unsigned ControlSource : 1;
			unsigned : 5;
		} b;
	}			tag_C_ProcessDataProperties;

	union {
		uint8_t	all;
		struct {
			unsigned TimeInterval : 1;
			unsigned DistanceInterval : 1;
			unsigned ThresholdLimits : 1;
			unsigned OnChange : 1;
			unsigned Total : 1;
			unsigned : 3;
		} b;
	}			tag_D_ProcessDataTrigger;

	char		tag_E_Designator[33];
	uint16_t	tag_F_DevValObjectID;
} t_uXML_DPD, *p_uXML_DPD;

// ------------------------
// D.24 Device Property DPT
typedef struct u_XML_DPT {
	uint16_t	tag_A_ObjectyID;
	uint16_t	tag_B_PropertyDDI;
	int32_t		tag_C_PropertyValue;
	char		tag_D_Designator[129];
	uint16_t	tag_E_DevValObjectID;
} t_uXML_DPT, *p_uXML_DPT;

// ----------------------------------
// D.25 Device Value Presentation DVP
typedef struct u_XML_DVP {
	uint16_t	tag_A_ObjectID;
	int32_t		tag_B_Offset;
	float		tag_C_Scale;
	uint8_t		tag_D_Decimals;
	char		tag_E_Designator[129];
} t_uXML_DVP, *p_uXML_DVP;

// ----------------------------
// D.22 Device Object Reference
typedef struct u_XML_DOR {
	uint16_t	tag_A_DevObjectID;
} t_uXML_DOR, *p_uXML_DOR;

// ------------------
// Linea XML rilevata
typedef struct u_XML_Line {
	uint8_t	tokenID;
	char	tag_Token[10];
	char	tag_A[129];
	char	tag_B[129];
	char	tag_C[129];
	char	tag_D[129];
	char	tag_E[129];
	char	tag_F[129];
	char	tag_G[129];
} t_uXML_Line, *p_uXML_Line;

// --------------------
// Limiti massimi array
#define	O_DET_MaxElements	200
#define	O_DOR_MaxElements	200
#define	O_DPD_MaxElements	200
#define	O_DPT_MaxElements	200
#define	O_DVP_MaxElements	200

// -----------------------------------
// Struttura per elementi di controllo
typedef struct u_Element_Check {
	uint16_t	Index;
	struct {
		uint16_t	Element;	// Codice dell'elemento DOR/DPD/DPT/DVP
		uint8_t		Found;		// Indica se elemento trovato
	} ID[O_DOR_MaxElements];
} t_KEY_Check, *p_KEY_Check;

// ------------------
// Registro di lavoro
struct u_regddop {
	uint16_t	ObjectID;		// ID progressivo degli oggetti DVC, DET

	uint8_t		DET_Level;		// Livello di nesting del Token DET
	uint16_t	DOR_Elements;	// Elementi DOR di DET

	t_KEY_Check	DOR_Check;		// Controllo ID DOR-DPD-DPT
	t_KEY_Check	DVP_Check;		// Controllo ID DVP

	t_uXML_Line	XML_Line;		// Linea XML letta
	t_uXML_DOR	XML_DOR[O_DOR_MaxElements];	// Elementi chiave xml DOR
};

extern struct u_regddop	gu_RegDDOP;