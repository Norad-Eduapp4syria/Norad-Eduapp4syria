# EA4S_WordDrawings - how to create the Drawings font

the art department provides a single grid with all drawings (rename it in SVG/EA4S_WordDrawings_grid.svg

1. Open it with Affinity Designer (maybe we could use Inkscape but i'm not sure it exports slices). check that every layer is named as the word_id in the Sheet.
2. Export all groups/layers as slices as SVG (for web) into the SVG/todo
3. Import all these single SVG files into Glyph (could be any OTF font maker), assigning the Unicode to the Sheet and moving the svg file into the "used" folder
4. make sure that every unicode id in Google Sheet WordData is unique
5. Export the OTF font into `/Assets/_app/Fonts/EA4S_WordDrawings.otf`
6. open TextMesh Pro Font Asset Creator using these parameters:
Font Source: EA4S_WordDrawings.otf
Font Size: Auto Sizing
Font padding: 5
Packing Method: Optimum
Atlas res: 1024x1024
Character Set: Unicode Range (Hex) with this Sequence:
100,102,103,104,10C,10E,10F,112,113,118,119,11A,122,123,12A,12B,12E,12F,136,137,14A,14B,152,153,175,177,2018,2019,201C,201D,2020,2021,2022,2026,2030,2039,203A,20AC,2190,2191,2192,2193,2194,2195,2196,2197,2198,2199,22,2202,2205,220F,2211,2212,221A,221E,222B,2248,2260,2264,2265,23,24,25,26,2669,266A,266B,266C,266D,266E,266F,27,28,29,2A,2B,2C,2D,2E,2F,30,300,301,302,307,308,31,32,33,34,35,36,37,38,39,3A,3B,3C,3D,3E,3F,40,41,42,43,44,45,46,47,48,49,4A,4B,4C,4D,4E,4F,50,51,52,53,54,55,56,57,58,59,5A,5B,5C,5D,5E,5F,61,62,63,64,65,66,67,68,69,6A,6B,6C,6D,6E,6F,70,71,72,73,74,75,76,77,78,79,7A,7B,7C,7D,7E,A1,A2,A3,A4,A5,A6,A7,A9,AB,AC,AE,B0,B1,B6,B7,BB,BF,C0,C1,C2,C4,C5,C6,C7,C8,C9,CA,CB,CC,CD,CE,CF,D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,DA,DB,DC,DD,DE,DF,E0,E1,E2,E3,E4,E5,E6,E7,E8,E9,EA,EB,EC,ED,EE,EF,F0,F1,F2,F3,F4,F5,F6,F7,F8,F9,FA,FB,FC,FD,FE,FF

Font Render Mode: Distance Field 32

TOTAL: 244 glyphs (with size 112)
