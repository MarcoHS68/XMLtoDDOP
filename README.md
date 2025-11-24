XMLtoDDOP - Conform to ISOBUS ISO11783-10:2015 specifications

This simple console program permits to convert a XML ISOBUS DDOP file into a C file that contains DDOP under a char array that will be transmitted to TC Server.

It also checks the consistency of the Object ID tags in DOR/DPD-DPT and DVP keys.

Usage: XMLtoDDOP [opt] [opt] [<XML_file.xml>] [<C_file.c>]

Options:

-d or -d0 = Debug: Insert XML lines into C file as comments

-d1 = Debug: Insert XML and Debug lines into C file as comments

-f array_name = Name the C array with array_name. Without this opzione the array will be named as DDOP_E2IS

-h = View help informations

-c = View credits information

Exaples:

XMLtoDDOP = Creates ddop.c file from ddop.xml source file with array name DDOP_E2IS

XMLtoDDOP -f DDOP_MINE = Creates ddop.c file from ddop.xml source file with array name DDOP_MINE

XMLtoDDOP ddop_tcbas.xml ddop_tcbas.c = Creates ddop_tcbas.c file from ddop_tcbas.xml source file

Notes:

XML comments <!-- ... --> are accepted and inserted into C file as comments

Tag B of DPD key is express in decimal. If you want to express it in hex, please add '0x' before number

Every line into the generated C file has comments that explain codes reported


Project was developed with VisualStudio2019 IDE
