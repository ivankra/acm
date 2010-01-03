#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main()
{
	int z[1001], N, T;

z[2] = -1;
z[3] = 3;
z[4] = -1;
z[5] = 5;
z[6] = 5;
z[7] = 5;
z[8] = 7;
z[9] = 7;
z[10] = 7;
z[11] = 7;
z[12] = 7;
z[13] = 7;
z[14] = 7;
z[15] = 7;
z[16] = 13;
z[17] = 13;
z[18] = 3;
z[19] = 3;
z[20] = 13;
z[21] = 13;
z[22] = 13;
z[23] = 13;
z[24] = 23;
z[25] = 23;
z[26] = 23;
z[27] = 23;
z[28] = 23;
z[29] = 23;
z[30] = 13;
z[31] = 13;
z[32] = 31;
z[33] = 31;
z[34] = 23;
z[35] = 23;
z[36] = 31;
z[37] = 31;
z[38] = 13;
z[39] = 13;
z[40] = 29;
z[41] = 29;
z[42] = -1;
z[43] = 43;
z[44] = 19;
z[45] = 19;
z[46] = 31;
z[47] = 31;
z[48] = 37;
z[49] = 37;
z[50] = 7;
z[51] = 7;
z[52] = 29;
z[53] = 29;
z[54] = 53;
z[55] = 53;
z[56] = 19;
z[57] = 19;
z[58] = 13;
z[59] = 13;
z[60] = 47;
z[61] = 47;
z[62] = 3;
z[63] = 3;
z[64] = 61;
z[65] = 61;
z[66] = 31;
z[67] = 31;
z[68] = 67;
z[69] = 67;
z[70] = 17;
z[71] = 17;
z[72] = 13;
z[73] = 13;
z[74] = 37;
z[75] = 37;
z[76] = 31;
z[77] = 31;
z[78] = 31;
z[79] = 31;
z[80] = 2;
z[81] = -1;
z[82] = -1;
z[83] = 83;
z[84] = 79;
z[85] = 79;
z[86] = 47;
z[87] = 47;
z[88] = 19;
z[89] = 19;
z[90] = 37;
z[91] = 37;
z[92] = 83;
z[93] = 83;
z[94] = 5;
z[95] = 5;
z[96] = 83;
z[97] = 83;
z[98] = 89;
z[99] = 89;
z[100] = 37;
z[101] = 37;
z[102] = 73;
z[103] = 73;
z[104] = 31;
z[105] = 31;
z[106] = 5;
z[107] = 5;
z[108] = 89;
z[109] = 89;
z[110] = 53;
z[111] = 53;
z[112] = 43;
z[113] = 43;
z[114] = 113;
z[115] = 113;
z[116] = 109;
z[117] = 109;
z[118] = 29;
z[119] = 29;
z[120] = 71;
z[121] = 71;
z[122] = 109;
z[123] = 109;
z[124] = 101;
z[125] = 101;
z[126] = 53;
z[127] = 53;
z[128] = 47;
z[129] = 47;
z[130] = 47;
z[131] = 47;
z[132] = 127;
z[133] = 127;
z[134] = 103;
z[135] = 103;
z[136] = 13;
z[137] = 13;
z[138] = 97;
z[139] = 97;
z[140] = 23;
z[141] = 23;
z[142] = 131;
z[143] = 131;
z[144] = 139;
z[145] = 139;
z[146] = 109;
z[147] = 109;
z[148] = 31;
z[149] = 31;
z[150] = 89;
z[151] = 89;
z[152] = 53;
z[153] = 53;
z[154] = 71;
z[155] = 71;
z[156] = 31;
z[157] = 31;
z[158] = 13;
z[159] = 13;
z[160] = 131;
z[161] = 131;
z[162] = 113;
z[163] = 113;
z[164] = 43;
z[165] = 43;
z[166] = 43;
z[167] = 43;
z[168] = 167;
z[169] = 167;
z[170] = 2;
z[171] = -1;
z[172] = -1;
z[173] = 173;
z[174] = 73;
z[175] = 73;
z[176] = 139;
z[177] = 139;
z[178] = 89;
z[179] = 89;
z[180] = 67;
z[181] = 67;
z[182] = 131;
z[183] = 131;
z[184] = 181;
z[185] = 181;
z[186] = 67;
z[187] = 67;
z[188] = 37;
z[189] = 37;
z[190] = 7;
z[191] = 7;
z[192] = 181;
z[193] = 181;
z[194] = 13;
z[195] = 13;
z[196] = 113;
z[197] = 113;
z[198] = 29;
z[199] = 29;
z[200] = 199;
z[201] = 199;
z[202] = 199;
z[203] = 199;
z[204] = 173;
z[205] = 173;
z[206] = 3;
z[207] = 3;
z[208] = 103;
z[209] = 103;
z[210] = 29;
z[211] = 29;
z[212] = 193;
z[213] = 193;
z[214] = 181;
z[215] = 181;
z[216] = 5;
z[217] = 5;
z[218] = 163;
z[219] = 163;
z[220] = 59;
z[221] = 59;
z[222] = 163;
z[223] = 163;
z[224] = 109;
z[225] = 109;
z[226] = 5;
z[227] = 5;
z[228] = 47;
z[229] = 47;
z[230] = 181;
z[231] = 181;
z[232] = 103;
z[233] = 103;
z[234] = 23;
z[235] = 23;
z[236] = 43;
z[237] = 43;
z[238] = 211;
z[239] = 211;
z[240] = 157;
z[241] = 157;
z[242] = 241;
z[243] = 241;
z[244] = 83;
z[245] = 83;
z[246] = 43;
z[247] = 43;
z[248] = 181;
z[249] = 181;
z[250] = 179;
z[251] = 179;
z[252] = 211;
z[253] = 211;
z[254] = 89;
z[255] = 89;
z[256] = 59;
z[257] = 59;
z[258] = 199;
z[259] = 199;
z[260] = 193;
z[261] = 193;
z[262] = 67;
z[263] = 67;
z[264] = 47;
z[265] = 47;
z[266] = 139;
z[267] = 139;
z[268] = 113;
z[269] = 113;
z[270] = 227;
z[271] = 227;
z[272] = 79;
z[273] = 79;
z[274] = 211;
z[275] = 211;
z[276] = 13;
z[277] = 13;
z[278] = 241;
z[279] = 241;
z[280] = 173;
z[281] = 173;
z[282] = 89;
z[283] = 89;
z[284] = 83;
z[285] = 83;
z[286] = 191;
z[287] = 191;
z[288] = 281;
z[289] = 281;
z[290] = 181;
z[291] = 181;
z[292] = 271;
z[293] = 271;
z[294] = 19;
z[295] = 19;
z[296] = 211;
z[297] = 211;
z[298] = 199;
z[299] = 199;
z[300] = 293;
z[301] = 293;
z[302] = 199;
z[303] = 199;
z[304] = 263;
z[305] = 263;
z[306] = 211;
z[307] = 211;
z[308] = 263;
z[309] = 263;
z[310] = 131;
z[311] = 131;
z[312] = 227;
z[313] = 227;
z[314] = 53;
z[315] = 53;
z[316] = 157;
z[317] = 157;
z[318] = 211;
z[319] = 211;
z[320] = 139;
z[321] = 139;
z[322] = 23;
z[323] = 23;
z[324] = 61;
z[325] = 61;
z[326] = 79;
z[327] = 79;
z[328] = 269;
z[329] = 269;
z[330] = 107;
z[331] = 107;
z[332] = 131;
z[333] = 131;
z[334] = 211;
z[335] = 211;
z[336] = 199;
z[337] = 199;
z[338] = 199;
z[339] = 199;
z[340] = 331;
z[341] = 331;
z[342] = 331;
z[343] = 331;
z[344] = 271;
z[345] = 271;
z[346] = 241;
z[347] = 241;
z[348] = 269;
z[349] = 269;
z[350] = 241;
z[351] = 241;
z[352] = 167;
z[353] = 167;
z[354] = 293;
z[355] = 293;
z[356] = 109;
z[357] = 109;
z[358] = 293;
z[359] = 293;
z[360] = 157;
z[361] = 157;
z[362] = 157;
z[363] = 157;
z[364] = 307;
z[365] = 307;
z[366] = 359;
z[367] = 359;
z[368] = 67;
z[369] = 67;
z[370] = 29;
z[371] = 29;
z[372] = 149;
z[373] = 149;
z[374] = 139;
z[375] = 139;
z[376] = 31;
z[377] = 31;
z[378] = 181;
z[379] = 181;
z[380] = 139;
z[381] = 139;
z[382] = 293;
z[383] = 293;
z[384] = 233;
z[385] = 233;
z[386] = 271;
z[387] = 271;
z[388] = 73;
z[389] = 73;
z[390] = 389;
z[391] = 389;
z[392] = 389;
z[393] = 389;
z[394] = 337;
z[395] = 337;
z[396] = 293;
z[397] = 293;
z[398] = 193;
z[399] = 193;
z[400] = 191;
z[401] = 191;
z[402] = 277;
z[403] = 277;
z[404] = 157;
z[405] = 157;
z[406] = 401;
z[407] = 401;
z[408] = 157;
z[409] = 157;
z[410] = 199;
z[411] = 199;
z[412] = 293;
z[413] = 293;
z[414] = 107;
z[415] = 107;
z[416] = 3;
z[417] = 3;
z[418] = 409;
z[419] = 409;
z[420] = 149;
z[421] = 149;
z[422] = 199;
z[423] = 199;
z[424] = 293;
z[425] = 293;
z[426] = 317;
z[427] = 317;
z[428] = 89;
z[429] = 89;
z[430] = 17;
z[431] = 17;
z[432] = 317;
z[433] = 317;
z[434] = 193;
z[435] = 193;
z[436] = 193;
z[437] = 193;
z[438] = 167;
z[439] = 167;
z[440] = 79;
z[441] = 79;
z[442] = 389;
z[443] = 389;
z[444] = 409;
z[445] = 409;
z[446] = 359;
z[447] = 359;
z[448] = 421;
z[449] = 421;
z[450] = 71;
z[451] = 71;
z[452] = 113;
z[453] = 113;
z[454] = 337;
z[455] = 337;
z[456] = 173;
z[457] = 173;
z[458] = 443;
z[459] = 443;
z[460] = 277;
z[461] = 277;
z[462] = 3;
z[463] = 3;
z[464] = 337;
z[465] = 337;
z[466] = 283;
z[467] = 283;
z[468] = 53;
z[469] = 53;
z[470] = 211;
z[471] = 211;
z[472] = 227;
z[473] = 227;
z[474] = 139;
z[475] = 139;
z[476] = 467;
z[477] = 467;
z[478] = 401;
z[479] = 401;
z[480] = 113;
z[481] = 113;
z[482] = 127;
z[483] = 127;
z[484] = 113;
z[485] = 113;
z[486] = 239;
z[487] = 239;
z[488] = 409;
z[489] = 409;
z[490] = 83;
z[491] = 83;
z[492] = 223;
z[493] = 223;
z[494] = 313;
z[495] = 313;
z[496] = 431;
z[497] = 431;
z[498] = 317;
z[499] = 317;
z[500] = 157;
z[501] = 157;
z[502] = 109;
z[503] = 109;
z[504] = 421;
z[505] = 421;
z[506] = 67;
z[507] = 67;
z[508] = 13;
z[509] = 13;
z[510] = 347;
z[511] = 347;
z[512] = 31;
z[513] = 31;
z[514] = 31;
z[515] = 31;
z[516] = 191;
z[517] = 191;
z[518] = 277;
z[519] = 277;
z[520] = 449;
z[521] = 449;
z[522] = 443;
z[523] = 443;
z[524] = 401;
z[525] = 401;
z[526] = 173;
z[527] = 173;
z[528] = 373;
z[529] = 373;
z[530] = 409;
z[531] = 409;
z[532] = 293;
z[533] = 293;
z[534] = 317;
z[535] = 317;
z[536] = 139;
z[537] = 139;
z[538] = 137;
z[539] = 137;
z[540] = 113;
z[541] = 113;
z[542] = 367;
z[543] = 367;
z[544] = 181;
z[545] = 181;
z[546] = 479;
z[547] = 479;
z[548] = 367;
z[549] = 367;
z[550] = 131;
z[551] = 131;
z[552] = 271;
z[553] = 271;
z[554] = 113;
z[555] = 113;
z[556] = 509;
z[557] = 509;
z[558] = 547;
z[559] = 547;
z[560] = 181;
z[561] = 181;
z[562] = 127;
z[563] = 127;
z[564] = 263;
z[565] = 263;
z[566] = 421;
z[567] = 421;
z[568] = 73;
z[569] = 73;
z[570] = 179;
z[571] = 179;
z[572] = 277;
z[573] = 277;
z[574] = 373;
z[575] = 373;
z[576] = 73;
z[577] = 73;
z[578] = 211;
z[579] = 211;
z[580] = 317;
z[581] = 317;
z[582] = 397;
z[583] = 397;
z[584] = 263;
z[585] = 263;
z[586] = 577;
z[587] = 577;
z[588] = 241;
z[589] = 241;
z[590] = 97;
z[591] = 97;
z[592] = 509;
z[593] = 509;
z[594] = 563;
z[595] = 563;
z[596] = 337;
z[597] = 337;
z[598] = 433;
z[599] = 433;
z[600] = 227;
z[601] = 227;
z[602] = 409;
z[603] = 409;
z[604] = 211;
z[605] = 211;
z[606] = 577;
z[607] = 577;
z[608] = 509;
z[609] = 509;
z[610] = 601;
z[611] = 601;
z[612] = 373;
z[613] = 373;
z[614] = 167;
z[615] = 167;
z[616] = 89;
z[617] = 89;
z[618] = 353;
z[619] = 353;
z[620] = 409;
z[621] = 409;
z[622] = 73;
z[623] = 73;
z[624] = 523;
z[625] = 523;
z[626] = 251;
z[627] = 251;
z[628] = 607;
z[629] = 607;
z[630] = 521;
z[631] = 521;
z[632] = 479;
z[633] = 479;
z[634] = 137;
z[635] = 137;
z[636] = 43;
z[637] = 43;
z[638] = 313;
z[639] = 313;
z[640] = 83;
z[641] = 83;
z[642] = 479;
z[643] = 479;
z[644] = 631;
z[645] = 631;
z[646] = 523;
z[647] = 523;
z[648] = 577;
z[649] = 577;
z[650] = 643;
z[651] = 643;
z[652] = 317;
z[653] = 317;
z[654] = 467;
z[655] = 467;
z[656] = 509;
z[657] = 509;
z[658] = 163;
z[659] = 163;
z[660] = 71;
z[661] = 71;
z[662] = 157;
z[663] = 157;
z[664] = 331;
z[665] = 331;
z[666] = 613;
z[667] = 613;
z[668] = 631;
z[669] = 631;
z[670] = 397;
z[671] = 397;
z[672] = 449;
z[673] = 449;
z[674] = 211;
z[675] = 211;
z[676] = 647;
z[677] = 647;
z[678] = 503;
z[679] = 503;
z[680] = 643;
z[681] = 643;
z[682] = 227;
z[683] = 227;
z[684] = 353;
z[685] = 353;
z[686] = 683;
z[687] = 683;
z[688] = 547;
z[689] = 547;
z[690] = 467;
z[691] = 467;
z[692] = 67;
z[693] = 67;
z[694] = 401;
z[695] = 401;
z[696] = 211;
z[697] = 211;
z[698] = 109;
z[699] = 109;
z[700] = 677;
z[701] = 677;
z[702] = 293;
z[703] = 293;
z[704] = 113;
z[705] = 113;
z[706] = 613;
z[707] = 613;
z[708] = 359;
z[709] = 359;
z[710] = 449;
z[711] = 449;
z[712] = 401;
z[713] = 401;
z[714] = 509;
z[715] = 509;
z[716] = 449;
z[717] = 449;
z[718] = 467;
z[719] = 467;
z[720] = 223;
z[721] = 223;
z[722] = 131;
z[723] = 131;
z[724] = 461;
z[725] = 461;
z[726] = 359;
z[727] = 359;
z[728] = 67;
z[729] = 67;
z[730] = 29;
z[731] = 29;
z[732] = 151;
z[733] = 151;
z[734] = 661;
z[735] = 661;
z[736] = 149;
z[737] = 149;
z[738] = 491;
z[739] = 491;
z[740] = 113;
z[741] = 113;
z[742] = 509;
z[743] = 509;
z[744] = 139;
z[745] = 139;
z[746] = 613;
z[747] = 613;
z[748] = 401;
z[749] = 401;
z[750] = 653;
z[751] = 653;
z[752] = 109;
z[753] = 109;
z[754] = 503;
z[755] = 503;
z[756] = 29;
z[757] = 29;
z[758] = 421;
z[759] = 421;
z[760] = 461;
z[761] = 461;
z[762] = 523;
z[763] = 523;
z[764] = 479;
z[765] = 479;
z[766] = 173;
z[767] = 173;
z[768] = 157;
z[769] = 157;
z[770] = 397;
z[771] = 397;
z[772] = 733;
z[773] = 733;
z[774] = 53;
z[775] = 53;
z[776] = 373;
z[777] = 373;
z[778] = 317;
z[779] = 317;
z[780] = 499;
z[781] = 499;
z[782] = 283;
z[783] = 283;
z[784] = 251;
z[785] = 251;
z[786] = 523;
z[787] = 523;
z[788] = 47;
z[789] = 47;
z[790] = 523;
z[791] = 523;
z[792] = 307;
z[793] = 307;
z[794] = 67;
z[795] = 67;
z[796] = 709;
z[797] = 709;
z[798] = 349;
z[799] = 349;
z[800] = 661;
z[801] = 661;
z[802] = 743;
z[803] = 743;
z[804] = 409;
z[805] = 409;
z[806] = 389;
z[807] = 389;
z[808] = 509;
z[809] = 509;
z[810] = 617;
z[811] = 617;
z[812] = 433;
z[813] = 433;
z[814] = 313;
z[815] = 313;
z[816] = 467;
z[817] = 467;
z[818] = 53;
z[819] = 53;
z[820] = 433;
z[821] = 433;
z[822] = 683;
z[823] = 683;
z[824] = 499;
z[825] = 499;
z[826] = 59;
z[827] = 59;
z[828] = 467;
z[829] = 467;
z[830] = 769;
z[831] = 769;
z[832] = 829;
z[833] = 829;
z[834] = 601;
z[835] = 601;
z[836] = 23;
z[837] = 23;
z[838] = 523;
z[839] = 523;
z[840] = 523;
z[841] = 523;
z[842] = 19;
z[843] = 19;
z[844] = 661;
z[845] = 661;
z[846] = 37;
z[847] = 37;
z[848] = 163;
z[849] = 163;
z[850] = 727;
z[851] = 727;
z[852] = 653;
z[853] = 653;
z[854] = 643;
z[855] = 643;
z[856] = 719;
z[857] = 719;
z[858] = 199;
z[859] = 199;
z[860] = 661;
z[861] = 661;
z[862] = 619;
z[863] = 619;
z[864] = 661;
z[865] = 661;
z[866] = 757;
z[867] = 757;
z[868] = 757;
z[869] = 757;
z[870] = 863;
z[871] = 863;
z[872] = 787;
z[873] = 787;
z[874] = 719;
z[875] = 719;
z[876] = 449;
z[877] = 449;
z[878] = 379;
z[879] = 379;
z[880] = 317;
z[881] = 317;
z[882] = 751;
z[883] = 751;
z[884] = 829;
z[885] = 829;
z[886] = 293;
z[887] = 293;
z[888] = 397;
z[889] = 397;
z[890] = 631;
z[891] = 631;
z[892] = 563;
z[893] = 563;
z[894] = 31;
z[895] = 31;
z[896] = 467;
z[897] = 467;
z[898] = 313;
z[899] = 313;
z[900] = 821;
z[901] = 821;
z[902] = 887;
z[903] = 887;
z[904] = 887;
z[905] = 887;
z[906] = 241;
z[907] = 241;
z[908] = 631;
z[909] = 631;
z[910] = 829;
z[911] = 829;
z[912] = 617;
z[913] = 617;
z[914] = 797;
z[915] = 797;
z[916] = 211;
z[917] = 211;
z[918] = 109;
z[919] = 109;
z[920] = 673;
z[921] = 673;
z[922] = 599;
z[923] = 599;
z[924] = 563;
z[925] = 563;
z[926] = 13;
z[927] = 13;
z[928] = 211;
z[929] = 211;
z[930] = 389;
z[931] = 389;
z[932] = 523;
z[933] = 523;
z[934] = 257;
z[935] = 257;
z[936] = 3;
z[937] = 3;
z[938] = 383;
z[939] = 383;
z[940] = 509;
z[941] = 509;
z[942] = 163;
z[943] = 163;
z[944] = 353;
z[945] = 353;
z[946] = 503;
z[947] = 503;
z[948] = 683;
z[949] = 683;
z[950] = 647;
z[951] = 647;
z[952] = 199;
z[953] = 199;
z[954] = 547;
z[955] = 547;
z[956] = 109;
z[957] = 109;
z[958] = 839;
z[959] = 839;
z[960] = 691;
z[961] = 691;
z[962] = 563;
z[963] = 563;
z[964] = 317;
z[965] = 317;
z[966] = 233;
z[967] = 233;
z[968] = 787;
z[969] = 787;
z[970] = 607;
z[971] = 607;
z[972] = 257;
z[973] = 257;
z[974] = 113;
z[975] = 113;
z[976] = 151;
z[977] = 151;
z[978] = 727;
z[979] = 727;
z[980] = 457;
z[981] = 457;
z[982] = 739;
z[983] = 739;
z[984] = 563;
z[985] = 563;
z[986] = 523;
z[987] = 523;
z[988] = 983;
z[989] = 983;
z[990] = 563;
z[991] = 563;
z[992] = 167;
z[993] = 167;
z[994] = 53;
z[995] = 53;
z[996] = 619;
z[997] = 619;
z[998] = 421;
z[999] = 421;
z[1000] = 127;

	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		printf(z[N] < 0 ? "B\n" : "A %d\n", z[N]);
	}
}

/*
#define SIEVE_SIZE 5000000
unsigned char sieve[SIEVE_SIZE/8+10];

bool isPrime(int n) {
	assert(n <= SIEVE_SIZE);
	return n >= 2 && ((sieve[n >> 3] >> (n & 7)) & 1) == 0;
}

void makeSieve() {
	for (int i = 2; i*i <= SIEVE_SIZE; i++) {
		if ((sieve[i >> 3] >> (i & 7)) & 1) continue;
		for (int j = i*i; j <= SIEVE_SIZE; j += i) {
			sieve[j >> 3] |= 1 << (j & 7);
		}
	}
}

int N;

// Assuming that n is a losing position, returns its preceding losing losion.
int pred(int n) {
	int x = n - N - 1;
	while (x >= 2) {
		if (isPrime(x)) return x;
		x--;
	}
	return 0;
}

#define LOG_PRED 12
int bigpred[LOG_PRED+1][SIEVE_SIZE+1];   // 2^k-th predecessors
void makeBig(int s)
{
	bigpred[0][s] = pred(s);
	for (int k = 1; k <= LOG_PRED; k++)
		bigpred[k][s] = bigpred[k-1][ bigpred[k-1][s] ];
}

void solve()
{
	int losing = -1;

	for (int i = 2; i <= N+2; i++)
		makeBig(i);

	// do a bruteforce to find some losing position
	for (int s = 2;; s++) {
		if (isPrime(s+N)) makeBig(s+N);
		if (!isPrime(s)) continue;

		// for any reachable prime s, interval [s, s+N] must contain
		// at least one losing position.

		// if position x is a losing position, this implies
		// that its predecessor pred(x) = largest prime in interval [2, x-N-1]
		// is also a losing position.

		// basic algorithm to find some losing position is to
		// take the set of all primes in [s, s+N] (which must contain at least one losing
		// position), and repeatedly find replace each number with its predecessor,
		// until the set becomes empty, or contains just a single number, which *has*
		// to be a losing position.
		// The algorithm is speed up by a space-time tradeoff - a table of
		// all 2^k-th predecessors of all occuring primes is computed.

		for (int k = 1; k <= LOG_PRED; k++) {
			int p = bigpred[k][s];
			if (p == 0) break;

			for (int i = 0; i <= N; i++) {
				if (isPrime(s+i)) {
					int q = bigpred[k][s+i];
					assert(q != 0);
					if (p != q) { p = 0; break; }
				}
			}

			if (p == 0) continue;

			// found a certainly losing position
			losing = p;
printf("[%d]", s);
			goto found;
		}
	}

found:
	// fast-forward to the origin
	while (true) {
		int p = pred(losing);
		if (p == 0) break;
		losing = p;
	}

	// now 'losing' is the first losing position in interval [2, ...]

	FILE *fp = fopen("cache.cc", "a");
	if (losing <= N) {
		printf("A %d\n", losing);
		fprintf(fp, "z[%d] = %d;\n", N, losing);
	} else {
		printf("B\n");
		fprintf(fp, "z[%d] = -1;\n", N);
	}
	fclose(fp);
}

int main()
{
	int T;
	makeSieve();
	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		solve();
	}
}
#endif
*/



/*
http://online-judge.uva.es/board/viewtopic.php?t=1666

SnapDragon
Tue Jan 14, 2003 9:33 pm

Here's how I thought about it when I made the problem. For each prime p, we determine the _unique_ first move for A that will allow A to force taking p. The reason that it is unique is simple: suppose A could pick both 'x' and 'y' as his first move to force taking p, with x < y. Then when A picks x, B could pick y and force taking p himself - a contradiction. And to ensure that there is ALWAYS a forcing move, pretend "A 0" is a valid first move (this is equivalent to a win for B).

So for every prime p, there is precisely one value 0 <= x <= n such that A can force taking p if and only if his first move is x. Let's call x the "forcing move" for p.

Now we can calculate this for each p. We start with the initial range of primes up to n (obviously). Then for successive p, note that the forcing move of p is the same as the forcing move of the maximum prime q that satisfies p-q > n. A just forces taking q, then B will have to take some prime between p-n and p-1, and then A can take p.

So there is an easy way to calculate the forcing move, and now all the question really asks for is the value at the (extremely large) p that is followed by a gap of size n. Of course, that's intractable for large n. But note that once a possible value of forcing move "drops out" of all the primes in a range slightly larger than n, IT CAN NEVER COME BACK. So in fact, random fluctuations will cause the forcing moves to homogenize as p gets large - the distribution of the primes serves as an effectively random perturbing factor to ensure this shakeout will happen. Further, the more primes a specific forcing move applies to, the more likely FUTURE primes will share that forcing move. So the homogenization actually occurs fairly quickly, as anyone who has solved this problem has observed.

Also, that's why you have a good chance of getting the right answer even if you don't go as far as necessary; the forcing move that will eventually win will probably already be in the majority. In fact, even if you stopped as soon as one forcing move takes over, say, 2/3rds of the primes in a range, and printed that one, you'd probably have an extremely high probability of correctness. (I haven't looked into it, so I'm not sure if there's a substantial time gain as a result)

This makes it clear that the problem is very CHAOTIC in nature; you have a bunch of forcing moves start out equally valid, and then very slight fluctuations in the prime distribution weed them out effectively randomly. It's like horse racing over the primes. I suspect that if you plotted the distribution of the "winners" over the starting range, it would be close to uniform. And there's surely no better way to predict (with certainty) the eventual winner than to simulate it. Interestingly enough, this may mean that the algorithm for this problem IS polynomial in runtime, but while we can argue it probabilistically, there may be no way to actually PROVE it. Cool, huh?

Anyway, that's probably more info than you cared to know. Heh.
*/
