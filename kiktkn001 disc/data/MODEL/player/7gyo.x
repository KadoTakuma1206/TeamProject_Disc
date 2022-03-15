xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 130;
 4.94019;-0.00216;4.91791;,
 7.72630;-2.78824;4.91791;,
 8.88032;-0.00216;4.91790;,
 4.94019;-3.94228;4.91790;,
 2.15412;-2.78824;4.91790;,
 1.00004;-0.00216;4.91791;,
 2.15411;2.78392;4.91791;,
 4.94019;3.93796;4.91790;,
 7.72630;2.78392;4.91790;,
 7.99285;-3.05479;4.84293;,
 9.25727;-0.00216;4.84292;,
 4.94020;-4.31924;4.84292;,
 1.88757;-3.05479;4.84292;,
 0.62315;-0.00216;4.84292;,
 1.88757;3.05047;4.84292;,
 4.94020;4.31492;4.84292;,
 7.99284;3.05047;4.84292;,
 8.21878;-3.28076;4.62939;,
 9.57683;-0.00216;4.62939;,
 4.94019;-4.63880;4.62939;,
 1.66160;-3.28076;4.62940;,
 0.30355;-0.00216;4.62940;,
 1.66160;3.27643;4.62940;,
 4.94019;4.63448;4.62939;,
 8.21878;3.27643;4.62939;,
 8.36977;-3.43175;4.30983;,
 9.79037;-0.00216;4.30983;,
 4.94020;-4.85233;4.30983;,
 1.51061;-3.43175;4.30983;,
 0.09006;-0.00216;4.30982;,
 1.51061;3.42743;4.30983;,
 4.94020;4.84801;4.30983;,
 8.36977;3.42743;4.30983;,
 8.42282;-3.48476;3.93287;,
 9.86535;-0.00216;3.93287;,
 4.94020;-4.92731;3.93288;,
 1.45759;-3.48476;3.93288;,
 0.01507;-0.00216;3.93287;,
 1.45759;3.48044;3.93288;,
 4.94020;4.92299;3.93288;,
 8.42282;3.48044;3.93287;,
 8.42278;-3.48476;2.80713;,
 9.86534;-0.00216;2.80713;,
 4.94019;-4.92731;2.80713;,
 1.45757;-3.48476;2.80712;,
 0.01508;-0.00216;2.80713;,
 1.45757;3.48044;2.80712;,
 4.94019;4.92299;2.80713;,
 8.42278;3.48044;2.80713;,
 8.42281;-3.48476;1.68137;,
 9.86534;-0.00216;1.68137;,
 4.94018;-4.92731;1.68136;,
 1.45757;-3.48476;1.68137;,
 0.01506;-0.00216;1.68138;,
 1.45757;3.48044;1.68137;,
 4.94018;4.92299;1.68136;,
 8.42281;3.48044;1.68138;,
 8.42281;-3.48476;0.55562;,
 9.86533;-0.00216;0.55564;,
 4.94020;-4.92731;0.55564;,
 1.45757;-3.48476;0.55563;,
 0.01508;-0.00216;0.55564;,
 1.45759;3.48044;0.55562;,
 4.94020;4.92299;0.55564;,
 8.42281;3.48044;0.55562;,
 8.42281;-3.48476;-0.57011;,
 9.86534;-0.00216;-0.57012;,
 4.94019;-4.92731;-0.57012;,
 1.45757;-3.48476;-0.57013;,
 0.01506;-0.00216;-0.57012;,
 1.45757;3.48044;-0.57013;,
 4.94019;4.92299;-0.57014;,
 8.42281;3.48044;-0.57011;,
 8.42278;-3.48476;-1.69587;,
 9.86530;-0.00216;-1.69587;,
 4.94019;-4.92731;-1.69588;,
 1.45761;-3.48476;-1.69587;,
 0.01506;-0.00216;-1.69587;,
 1.45761;3.48044;-1.69587;,
 4.94019;4.92299;-1.69588;,
 8.42278;3.48044;-1.69587;,
 8.42282;-3.48476;-2.82162;,
 9.86533;-0.00216;-2.82162;,
 4.94018;-4.92731;-2.82163;,
 1.45760;-3.48476;-2.82162;,
 0.01508;-0.00216;-2.82161;,
 1.45760;3.48044;-2.82162;,
 4.94018;4.92299;-2.82163;,
 8.42282;3.48044;-2.82162;,
 8.42280;-3.48476;-3.94738;,
 9.86533;-0.00216;-3.94737;,
 4.94023;-4.92731;-3.94737;,
 1.45759;-3.48476;-3.94738;,
 0.01506;-0.00216;-3.94737;,
 1.45759;3.48044;-3.94738;,
 4.94023;4.92299;-3.94737;,
 8.42280;3.48044;-3.94736;,
 8.36979;-3.43175;-4.32433;,
 9.79036;-0.00216;-4.32433;,
 4.94023;-4.85233;-4.32433;,
 1.51061;-3.43175;-4.32432;,
 0.09002;-0.00216;-4.32432;,
 1.51061;3.42743;-4.32432;,
 4.94023;4.84801;-4.32433;,
 8.36979;3.42743;-4.32433;,
 8.21879;-3.28076;-4.64389;,
 9.57686;-0.00216;-4.64389;,
 4.94020;-4.63880;-4.64390;,
 1.66162;-3.28076;-4.64391;,
 0.30356;-0.00216;-4.64390;,
 1.66162;3.27644;-4.64391;,
 4.94020;4.63448;-4.64390;,
 8.21879;3.27644;-4.64389;,
 7.99282;-3.05479;-4.85742;,
 9.25726;-0.00216;-4.85742;,
 4.94022;-4.31924;-4.85741;,
 1.88758;-3.05479;-4.85741;,
 0.62315;-0.00216;-4.85743;,
 1.88758;3.05047;-4.85741;,
 4.94022;4.31492;-4.85741;,
 7.99282;3.05047;-4.85742;,
 7.72631;-2.78825;-4.93240;,
 8.88033;-0.00216;-4.93240;,
 4.94020;-3.94228;-4.93240;,
 2.15413;-2.78825;-4.93240;,
 1.00006;-0.00216;-4.93240;,
 2.15413;2.78392;-4.93240;,
 4.94020;3.93796;-4.93240;,
 7.72631;2.78392;-4.93240;,
 4.94020;-0.00216;-4.93240;;
 
 136;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 4;74,73,81,82;,
 4;73,75,83,81;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,74,82,88;,
 4;82,81,89,90;,
 4;81,83,91,89;,
 4;83,84,92,91;,
 4;84,85,93,92;,
 4;85,86,94,93;,
 4;86,87,95,94;,
 4;87,88,96,95;,
 4;88,82,90,96;,
 4;90,89,97,98;,
 4;89,91,99,97;,
 4;91,92,100,99;,
 4;92,93,101,100;,
 4;93,94,102,101;,
 4;94,95,103,102;,
 4;95,96,104,103;,
 4;96,90,98,104;,
 4;98,97,105,106;,
 4;97,99,107,105;,
 4;99,100,108,107;,
 4;100,101,109,108;,
 4;101,102,110,109;,
 4;102,103,111,110;,
 4;103,104,112,111;,
 4;104,98,106,112;,
 4;106,105,113,114;,
 4;105,107,115,113;,
 4;107,108,116,115;,
 4;108,109,117,116;,
 4;109,110,118,117;,
 4;110,111,119,118;,
 4;111,112,120,119;,
 4;112,106,114,120;,
 4;114,113,121,122;,
 4;113,115,123,121;,
 4;115,116,124,123;,
 4;116,117,125,124;,
 4;117,118,126,125;,
 4;118,119,127,126;,
 4;119,120,128,127;,
 4;120,114,122,128;,
 3;122,121,129;,
 3;121,123,129;,
 3;123,124,129;,
 3;124,125,129;,
 3;125,126,129;,
 3;126,127,129;,
 3;127,128,129;,
 3;128,122,129;;
 
 MeshMaterialList {
  4;
  136;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.153725;0.279216;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.530196;0.235294;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  130;
  0.000001;0.000000;1.000000;,
  0.097852;0.000002;0.995201;,
  0.069191;-0.069191;0.995201;,
  -0.000002;-0.097852;0.995201;,
  -0.069198;-0.069196;0.995200;,
  -0.097868;0.000000;0.995199;,
  -0.069202;0.069199;0.995200;,
  -0.000000;0.097854;0.995201;,
  0.069192;0.069191;0.995201;,
  0.380625;-0.000000;0.924730;,
  0.269143;-0.269140;0.924730;,
  0.000002;-0.380614;0.924734;,
  -0.269126;-0.269128;0.924739;,
  -0.380603;0.000001;0.924739;,
  -0.269131;0.269133;0.924735;,
  0.000001;0.380615;0.924733;,
  0.269139;0.269137;0.924732;,
  0.704981;-0.000002;0.709226;,
  0.498500;-0.498499;0.709222;,
  0.000002;-0.704980;0.709227;,
  -0.498494;-0.498495;0.709230;,
  -0.704979;-0.000000;0.709229;,
  -0.498493;0.498493;0.709232;,
  0.000002;0.704975;0.709232;,
  0.498494;0.498494;0.709230;,
  0.923092;-0.000001;0.384579;,
  0.652727;-0.652729;0.384568;,
  -0.000000;-0.923103;0.384553;,
  -0.652739;-0.652733;0.384541;,
  -0.923111;-0.000001;0.384535;,
  -0.652738;0.652731;0.384545;,
  -0.000000;0.923100;0.384559;,
  0.652726;0.652727;0.384572;,
  0.995171;-0.000000;0.098157;,
  0.703692;-0.703693;0.098153;,
  0.000001;-0.995172;0.098149;,
  -0.703695;-0.703690;0.098156;,
  -0.995171;-0.000000;0.098161;,
  -0.703695;0.703690;0.098155;,
  0.000000;0.995172;0.098149;,
  0.703692;0.703692;0.098152;,
  1.000000;-0.000000;-0.000005;,
  0.707107;-0.707106;-0.000004;,
  0.000000;-1.000000;-0.000000;,
  -0.707110;-0.707103;0.000005;,
  -1.000000;-0.000000;0.000005;,
  -0.707110;0.707103;0.000004;,
  0.000000;1.000000;-0.000001;,
  0.707107;0.707106;-0.000005;,
  1.000000;-0.000000;0.000003;,
  0.707108;-0.707106;0.000003;,
  0.000000;-1.000000;0.000001;,
  -0.707110;-0.707103;-0.000001;,
  -1.000000;-0.000000;-0.000001;,
  -0.707110;0.707104;-0.000002;,
  -0.000000;1.000000;0.000001;,
  0.707108;0.707106;0.000003;,
  1.000000;-0.000000;0.000000;,
  0.707108;-0.707105;0.000001;,
  0.000000;-1.000000;0.000001;,
  -0.707110;-0.707104;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.707110;0.707104;-0.000000;,
  0.000000;1.000000;0.000001;,
  0.707109;0.707105;0.000001;,
  1.000000;-0.000000;-0.000011;,
  0.707109;-0.707105;-0.000007;,
  0.000000;-1.000000;-0.000003;,
  -0.707109;-0.707105;-0.000002;,
  -1.000000;0.000000;-0.000001;,
  -0.707109;0.707105;-0.000001;,
  0.000000;1.000000;-0.000003;,
  0.707109;0.707105;-0.000007;,
  1.000000;-0.000000;-0.000000;,
  0.707109;-0.707105;-0.000001;,
  -0.000001;-1.000000;-0.000002;,
  -0.707108;-0.707105;-0.000007;,
  -1.000000;-0.000000;-0.000011;,
  -0.707108;0.707105;-0.000006;,
  -0.000001;1.000000;-0.000001;,
  0.707109;0.707104;-0.000000;,
  1.000000;-0.000000;0.000008;,
  0.707109;-0.707104;0.000006;,
  -0.000001;-1.000000;0.000002;,
  -0.707109;-0.707105;0.000002;,
  -1.000000;-0.000000;0.000005;,
  -0.707109;0.707105;0.000002;,
  -0.000001;1.000000;0.000002;,
  0.707109;0.707104;0.000006;,
  0.995173;-0.000000;-0.098134;,
  0.703696;-0.703691;-0.098136;,
  0.000002;-0.995172;-0.098144;,
  -0.703694;-0.703692;-0.098144;,
  -0.995173;-0.000000;-0.098138;,
  -0.703693;0.703692;-0.098146;,
  0.000002;0.995172;-0.098145;,
  0.703696;0.703691;-0.098136;,
  0.923115;-0.000000;-0.384523;,
  0.652740;-0.652735;-0.384535;,
  0.000001;-0.923107;-0.384543;,
  -0.652734;-0.652737;-0.384543;,
  -0.923105;-0.000000;-0.384549;,
  -0.652733;0.652736;-0.384546;,
  0.000001;0.923106;-0.384547;,
  0.652740;0.652734;-0.384536;,
  0.704968;-0.000000;-0.709239;,
  0.498487;-0.498489;-0.709239;,
  0.000002;-0.704968;-0.709239;,
  -0.498483;-0.498486;-0.709244;,
  -0.704958;-0.000000;-0.709249;,
  -0.498482;0.498486;-0.709244;,
  0.000002;0.704967;-0.709240;,
  0.498487;0.498488;-0.709239;,
  0.380603;-0.000000;-0.924738;,
  0.269130;-0.269132;-0.924736;,
  0.000001;-0.380608;-0.924737;,
  -0.269125;-0.269127;-0.924739;,
  -0.380598;-0.000000;-0.924741;,
  -0.269125;0.269127;-0.924739;,
  0.000001;0.380609;-0.924736;,
  0.269130;0.269132;-0.924736;,
  0.097866;-0.000000;-0.995200;,
  0.069201;-0.069199;-0.995200;,
  -0.000002;-0.097864;-0.995200;,
  -0.069201;-0.069203;-0.995200;,
  -0.097864;-0.000000;-0.995200;,
  -0.069201;0.069202;-0.995200;,
  -0.000002;0.097863;-0.995200;,
  0.069200;0.069198;-0.995200;,
  -0.000000;-0.000000;-1.000000;;
  136;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,73,81,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,81,89,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,89,97,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,97,105,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,105,113,120;,
  4;113,114,122,121;,
  4;114,115,123,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;117,118,126,125;,
  4;118,119,127,126;,
  4;119,120,128,127;,
  4;120,113,121,128;,
  3;121,122,129;,
  3;122,123,129;,
  3;123,124,129;,
  3;124,125,129;,
  3;125,126,129;,
  3;126,127,129;,
  3;127,128,129;,
  3;128,121,129;;
 }
 MeshTextureCoords {
  130;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}