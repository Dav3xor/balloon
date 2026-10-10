#ifndef __WISHLIST_H__
#define __WISHLIST_H__

typedef struct Target { // lat long in decimal degrees\n")
    float lat;
    float lon;
    float distance;
    uint16_t priority;
    uint16_t flags;
    uint32_t id;
} __attribute__((__packed__)) Target;

inline Target targets[] = { 
    {     39.9033,     116.392,  2.0, 0,     1 }, // Tiananman Square      -            
    {     51.5072,     -0.1275,  5.0, 0,     2 }, // London                -            
    {     48.8567,      2.3522,  5.0, 0,     3 }, // Paris                 -            
    {          45,        -123,  5.0, 0,     6 }, // Salem Oregon          -            
    {       45.52,    -122.682,  5.0, 0,    10 }, // Portland Oregon       - Portland ( PORT-lənd) is the m 
    {        18.3,    -64.8253,  1.0, 0,    11 }, // Epstein Island        - Little Saint James, nicknamed  
    {       37.85,    -119.517,  5.0, 0,    15 }, // Yosemite              - Yosemite National Park ( yoh-S 
    {        44.6,      -110.5,  5.0, 0,    16 }, // yellowstone           - Yellowstone National Park is a 
    {        9.12,      -79.75,  2.0, 0,    17 }, // panama canal          - The Panama Canal (Spanish: Can 
    {     27.9883,     86.9253,  2.0, 0,    18 }, // Mount Everest         - Mount Everest (known in Nepali 
    {     35.8825,     76.5133,  2.0, 0,    19 }, // K2                    - K2, also known as Mount Godwin 
    {     51.2722,     30.2242,  3.0, 0,    21 }, // Chornobyl             - Chernobyl, also known as Chorn 
    {      55.067,     82.9835,  2.0, 0,    22 }, // Novosibirsk Sukhoi aircraft factory  -            
    {     55.2015,      61.424,  3.0, 0,    23 }, // Chelyabinsk Electrochemical Plant  -            
    {     55.2005,     61.3751,  4.0, 0,    24 }, // Chelyabinsk Electric Locomotive  -            
    {     55.1555,     61.4704,  3.0, 0,    25 }, // Chelyabinsk Tractor Plant  -            
    {      37.984,     58.3671,  5.0, 0,    26 }, // Turkmenistan Ashkebat Airport  -            
    {     37.9016,     58.3765,  5.0, 0,    27 }, // Turkmenistan Ashkebat downtown  -            
    {     37.8986,     58.3081,  5.0, 0,    28 }, // Turkmenistan Archabil park  -            
    {     41.9402,     48.3784,  5.0, 0,    29 }, // Caspian Sea Monster   -            
    {     48.7423,     44.5371,  5.0, 0,    30 }, // The Motherland Calls Volgograd  -            
    {     54.1993,     37.6204,  3.0, 0,    31 }, // Tula Arsenal          -            
    {     54.2202,     37.7133,  2.0, 0,    32 }, // Tula KBP 1            -            
    {     54.2267,     37.6954,  2.0, 0,    33 }, // tula Pantsir Factory  -            
    {     54.2217,     37.6957,  2.0, 0,    34 }, // Tula MLRS Factory     -            
    {     54.2307,     37.6814,  4.0, 0,    35 }, // Tula Technopark (guard with fatigues on streetview)  -            
    {     58.0493,     38.8092,  5.0, 0,    36 }, // Rybinsk Saturn Jet Engines 2  -            
    {     58.0956,     38.7532,  5.0, 0,    37 }, // Rybinsk more saturn? 4  -            
    {     73.8072,     54.9817,  5.0, 0,    38 }, // Tsar Bomba site       -            
    {     51.4812,     46.2096,  2.0, 0,    39 }, // Engels AFB Saratov    -            
    {     51.5678,     46.0253,  2.0, 0,    40 }, // Saratov Po Korpus INS manufacturer  -            
    {     57.2017,     33.0635,  2.0, 0,    41 }, // Gorodomlya Island     -            
    {     51.6426,     39.2543,  5.0, 0,    42 }, // Voronetz PAO Vasa Aircraft plant/airfield 3  -            
    {     48.7714,      2.2043,  5.0, 0,    43 }, // Paris Villacoublay airfield  -            
    {     48.8583,     2.29436,  5.0, 0,    44 }, // Paris Eifel Tower     -            
    {     44.5995,     33.5281,  2.0, 0,    45 }, // Sevastopol Pivdenna Bay 1  -            
    {     44.6055,     33.5317,  2.0, 0,    46 }, // Sevastopol Pivdenna Bay 2  -            
    {     44.6132,     33.5303,  2.0, 0,    47 }, // Sevastopol Pivdenna Bay 3  -            
    {     44.6263,      33.555,  2.0, 0,    48 }, // Sevastopol Oil Terminal Dry dock  -            
    {     45.3602,     36.4792,  2.0, 0,    49 }, // Kerch Ferry Terminal  -            
    {     45.3285,     36.4683,  2.0, 0,    50 }, // Kerch Bridge approach  -            
    {     45.3088,     36.5062,  2.0, 0,    51 }, // Kerch Bridge mid span  -            
    {      46.728,     38.2774,  2.0, 0,    52 }, // Kerch/Yeysk Ferry Terminal  -            
    {     45.3412,     36.6735,  2.0, 0,    53 }, // Kerch/Chuska Ferry Termain  -            
    {     44.7253,     37.7951,  2.0, 0,    54 }, // Novorossiysk Port     -            
    {     46.7533,     36.7787,  2.0, 0,    55 }, // Berdyansk Port        -            
    {     47.0961,     37.5483,  3.0, 0,    56 }, // Mariupol Drama Theater "Children"  -            
    {     56.3594,     43.8765,  3.0, 0,    57 }, // Nizhny Novgorod Krasnoe Sormovo Submarine Plant  -            
    {     56.3242,     43.8568,  3.0, 0,    58 }, // Sokol Aircraft Plant (Mig-31...)  -            
    {     56.3263,     43.9065,  2.0, 0,    59 }, // Nizhny Novgorod Almaz/Antey  -            
    {     34.2961,      132.32,  5.0, 0,    60 }, // Miyajima Island Japan  -            
    {     35.3676,     138.738,  5.0, 0,    61 }, // Mount Fuji            -            
    {     34.3965,     132.453,  5.0, 0,    62 }, // Hiroshima triple bridge  -            
    {     39.0363,     125.731,  5.0, 0,    63 }, // Ryugyong Hotel Pyongyang  -            
    {     41.9933,     128.078,  5.0, 0,    64 }, // Mount Paektu          -            
    {     39.7975,     125.755,  5.0, 0,    65 }, // yongbyong nuclear science and weapons center  -            
    {     38.9571,     125.612,  5.0, 0,    66 }, // kangson nuclear enrichment  -            
    {     47.5578,     10.7493,  5.0, 0,    67 }, // Neuschwanstein        -            
    {     48.8131,     2.08858,  5.0, 0,    68 }, // Versailles 1          -            
    {     48.8103,     2.10046,  5.0, 0,    69 }, // Versailles 2          -            
    {     48.8058,     2.11756,  5.0, 0,    70 }, // Versailles 3          -            
    {      51.506,   -0.184405,  5.0, 0,    71 }, // Kensington Palace     -            
    {     40.5241,     -108.99,  5.0, 0,    72 }, // Steamboat Rock Colorado  -            
    {     41.7341,    -111.828,  5.0, 0,    73 }, // Logan Utah Temple     -            
    {     40.7705,    -111.892,  5.0, 0,    74 }, // Salt Lake City Temple  -            
    {     43.0481,     -115.87,  5.0, 0,    75 }, // Mountain Home AFB     -            
    {     45.8365,    -119.431,  5.0, 0,    76 }, // Hermiston Chemical Weapons Dump  -            
    {     38.0982,     -78.487,  5.0, 0,    77 }, // Virginia Rowing       -            
    {     38.1108,    -78.4989,  5.0, 0,    78 }, // Rowenna River         -            
    {     19.4813,    -155.933,  5.0, 0,    79 }, // Hawaii Captain Cook monument  -            
    {     21.3638,     -157.96,  5.0, 0,    80 }, // Ford Island           -            
    {     21.3508,     -157.96,  5.0, 0,    81 }, // Pearl Harbor 1        -            
    {      21.358,    -157.945,  5.0, 0,    82 }, // Pearl Harbor 2        -            
    {     21.3649,     -157.95,  5.0, 0,    83 }, // USS Arizona Memorial  -            
    {     40.7515,    -73.9754,  5.0, 0,    84 }, // Chryslter Building    -            
    {      48.861,     2.33782,  5.0, 0,    85 }, // The Louvre            -            
    {     29.9766,     31.1311,  5.0, 0,    86 }, // Ghiza Pyramids        -            
    {     31.5344,     34.5122,  5.0, 0,    87 }, // Gaza Strip 1          -            
    {     31.5124,     34.4709,  5.0, 0,    88 }, // Gaza Strip 2          -            
    {     31.4788,     34.4337,  5.0, 0,    89 }, // Gaza Strip 3          -            
    {     31.4512,     34.4137,  5.0, 0,    90 }, // Gaza Strip 4          -            
    {     31.4201,     34.3695,  5.0, 0,    91 }, // Gaza Strip 5          -            
    {      31.396,     34.3424,  5.0, 0,    92 }, // Gaza Strip 6          -            
    {     31.3589,     34.3218,  5.0, 0,    93 }, // Gaza Strip 7          -            
    {     31.3287,     34.2883,  5.0, 0,    94 }, // Gaza STrip 8          -            
    {     31.2855,     34.2518,  5.0, 0,    95 }, // Gaza Strip 9          -            
    {     28.6265,    -80.6216,  5.0, 0,    96 }, // Launch Complex 39B    -            
    {     28.6088,    -80.6057,  5.0, 0,    97 }, // Launch Complex 39A    -            
    {      28.584,     -80.582,  5.0, 0,    98 }, // Launch Complex 41     -            
    {     28.5617,    -80.5772,  5.0, 0,    99 }, // SpaceX Launch         -            
    {     28.5521,    -80.5898,  5.0, 0,   100 }, // more cape canaveral   -            
    {     28.5435,    -80.5909,  5.0, 0,   101 }, // more cape canaveral 2  -            
    {     28.5305,    -80.5933,  5.0, 0,   102 }, // more cape canaveral 3  -            
    {     28.5324,    -80.5666,  5.0, 0,   103 }, // more cape canaveral 4  -            
    {     28.5234,    -80.5718,  5.0, 0,   104 }, // more cape canaveral 5  -            
    {     28.5218,     -80.561,  5.0, 0,   105 }, // launch complex 34     -            
    {     28.5184,    -80.5635,  5.0, 0,   106 }, // apollo launch complex  -            
    {     28.5121,     -80.557,  5.0, 0,   107 }, // slc-20                -            
    {      28.507,    -80.5541,  5.0, 0,   108 }, // titan launch complex (gemini)  -            
    {      28.502,    -80.5522,  5.0, 0,   109 }, // more canaveral        -            
    {     28.4964,    -80.5494,  5.0, 0,   110 }, // launch complex 14     -            
    {     28.4911,    -80.5472,  5.0, 0,   111 }, // stoke space           -            
    {     28.4868,    -80.5447,  5.0, 0,   112 }, // spacex landing zone   -            
    {     28.4808,    -80.5418,  5.0, 0,   113 }, // landing complex 12    -            
    {     28.4726,     -80.539,  5.0, 0,   114 }, // blue origin           -            
    {     28.4599,    -80.5422,  5.0, 0,   115 }, // cape canaveral light house  -            
    {     28.4529,     -80.556,  5.0, 0,   116 }, // minuteman test site   -            
    {     28.4483,    -80.5645,  5.0, 0,   117 }, // launch complexes 17&18  -            
    {      28.443,    -80.5717,  5.0, 0,   118 }, // cape canaveral space force museum  -            
    {     28.4336,    -80.5894,  5.0, 0,   119 }, // naval ordnance test unit headquarters  -            
    {     28.3918,    -80.6077,  5.0, 0,   120 }, // cape canaveral (the town)  -            
    {     19.9127,    -75.1618,  5.0, 0,   121 }, // Gitmo NEX minimart    -            
    {     19.9115,    -75.1547,  5.0, 0,   122 }, // Gitmo Vectrus System Headquarters  -            
    {     19.9173,    -75.1475,  5.0, 0,   123 }, // Gitmo Dive Locker     -            
    {     19.9247,    -75.1406,  5.0, 0,   124 }, // Jerk GTMO             -            
    {     19.9332,    -75.1318,  5.0, 0,   125 }, // Marine Hill Liberty Center  -            
    {     19.9034,    -75.0966,  5.0, 0,   126 }, // GTMO detention center  -            
    {     -33.857,     151.215,  5.0, 0,   127 }, // Sydney Opera House    -            
    {    -25.3437,     131.035,  5.0, 0,   128 }, // Uluru-Kata Tjuta National Park  -            
    {     38.9522,    -77.1451,  5.0, 0,   129 }, // CIA                   -            
    {     38.8709,    -77.0555,  5.0, 0,   130 }, // Pentagon              -            
    {     38.8898,    -77.0496,  5.0, 0,   131 }, // Licoln Memorial       -            
    {       38.89,    -77.0093,  5.0, 0,   132 }, // US Capitol            -            
    {     39.3327,    -76.6234,  5.0, 0,   133 }, // Space Telescope Science Institute  -            
    {     39.2842,    -76.6099,  5.0, 0,   134 }, // Baltimore Harbor      -            
    {     39.2146,    -76.5313,  5.0, 0,   135 }, // Francis Scott Key Bridge  -            
    {     39.1086,    -76.7716,  5.0, 0,   136 }, // The NSA               -            
    {     39.1149,    -76.7747,  5.0, 0,   137 }, // National Cryptologic Museum  -            
    {      37.308,    -76.6251,  5.0, 0,   138 }, // The Farm  track       -            
    {     37.3113,    -76.6392,  5.0, 0,   139 }, // The Farm airfield     -            
    {     37.3081,    -76.6816,  5.0, 0,   140 }, // The Farm entrance     -            
    {     37.3515,    -76.6649,  5.0, 0,   141 }, // The farm housing      -            
    {     37.3172,    -76.6479,  5.0, 0,   142 }, // more The Farm         -            
    {     36.9988,    -76.4475,  5.0, 0,   143 }, // Newport News 1        -            
    {     36.9865,    -76.4408,  5.0, 0,   144 }, // Newport News 2        -            
    {     36.9714,    -76.4296,  5.0, 0,   145 }, // Newport News 3        -            
    {     35.2529,    -81.1579,  5.0, 0,   146 }, // Schiele Museum of Natural History  -            
    {     24.5542,     -81.794,  5.0, 0,   147 }, // Key West              -            
    {     8.93738,    -79.5591,  5.0, 0,   148 }, // Panama Canal 1        -            
    {     8.95432,    -79.5705,  5.0, 0,   149 }, // Panama Canal 2        -            
    {     8.97983,    -79.5858,  5.0, 0,   150 }, // Panama Canal 3        -            
    {     8.99751,    -79.5919,  5.0, 0,   151 }, // Panama Canal 4        -            
    {     9.01779,    -79.6128,  5.0, 0,   152 }, // Panama Canal 5        -            
    {     9.09353,    -79.6828,  5.0, 0,   153 }, // Panama Canal Culebra Cut  -            
    {     9.27093,     -79.914,  5.0, 0,   154 }, // Panama Canal 6        -            
    {     9.35655,    -79.8956,  5.0, 0,   155 }, // Panama Canal Colon    -            
    {     8.15481,    -77.6917,  5.0, 0,   156 }, // Yaviza                -            
    {     7.72001,    -77.5615,  5.0, 0,   157 }, // Darian Gap            -            
    {     14.1303,     38.7197,  5.0, 0,   158 }, // Axum Tsion St. Mary (The Ark)  -            
    {     54.7099,     20.5098,  5.0, 0,   159 }, // Konigsberg Castle     -            
    {    -7.31303,     72.4153,  5.0, 0,   160 }, // Diego Garcia airport  -            
    {     -7.2939,      72.391,  5.0, 0,   161 }, // Diego Garcia Port/Oil Terminal  -            
    {    -7.27822,     72.3654,  5.0, 0,   162 }, // Diego Garcia radar/satellite domes  -            
    {    -7.26629,      72.363,  5.0, 0,   163 }, // Diego Garcia more radar/sat  -            
    {    -7.26267,     72.3764,  5.0, 0,   164 }, // Diego Garcia Naval Base  -            
    {    -7.34986,     72.4325,  5.0, 0,   165 }, // Diego Garcia Dump?    -            
    {    -7.37568,     72.4287,  5.0, 0,   166 }, // Diego Garcia ?        -            
    {    -7.38555,     72.4245,  5.0, 0,   167 }, // Diego Garcia Storage  -            
    {    -7.41204,     72.4207,  5.0, 0,   168 }, // Diego Garcia ...guard tower?  -            
    {    -7.43046,     72.4429,  5.0, 0,   169 }, // Diego Garcia buildings  -            
    {    -7.41235,     72.4526,  5.0, 0,   170 }, // Diego Garcia Ground Based Electro-Optical Deep Space Surveillance  -            
    {    -7.40245,     72.4618,  5.0, 0,   171 }, // Diego Garcia disturbed ground  -            
    {     35.0564,    -118.161,  5.0, 0,   172 }, // Mojave Airport Scaled Composites  -            
    {     35.0482,    -118.142,  5.0, 0,   173 }, // Mojave Airport Stratolaunch  -            
    {     34.9867,    -117.862,  5.0, 0,   174 }, // Edwards North Aux Base  -            
    {     34.9541,    -117.873,  5.0, 0,   175 }, // Edwards compass rose  -            
    {     34.9497,    -117.888,  5.0, 0,   176 }, // Edwards AFB north end  -            
    {     34.9125,    -117.903,  5.0, 0,   177 }, // Edwards AFB south end  -            
    {     34.8996,    -117.872,  5.0, 0,   178 }, // Edwards AFB south base  -            
    {     46.7413,    -116.969,  5.0, 0,   179 }, // Doug Wilson Christ Church Hall  -            
    {     38.9034,    -77.0263,  5.0, 0,   180 }, // Cato Institute        -            
};

inline uint32_t sorted_targets [171];


#endif
