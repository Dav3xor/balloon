#ifndef __WISHLIST_H__
#define __WISHLIST_H__

#define NUM_TARGETS 171
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
    {       37.85,    -119.517,  5.0, 0,    15 }, // Yosemite              - Yosemite National Park ( yoh-S 
    {        44.6,      -110.5,  5.0, 0,    16 }, // yellowstone           - Yellowstone National Park is a 
    {        9.12,      -79.75,  2.0, 0,    17 }, // panama canal          - The Panama Canal (Spanish: Can 
    {     27.9883,     86.9253,  2.0, 0,    18 }, // Mount Everest         - Mount Everest (known in Nepali 
    {     35.8825,     76.5133,  2.0, 0,    19 }, // K2                    - K2, also known as Mount Godwin    
    {     47.5578,     10.7493,  5.0, 0,    67 }, // Neuschwanstein        -            
    {     48.8131,     2.08858,  5.0, 0,    68 }, // Versailles 1          -            
    {     48.8103,     2.10046,  5.0, 0,    69 }, // Versailles 2          -            
    {     48.8058,     2.11756,  5.0, 0,    70 }, // Versailles 3          -            
    {      51.506,   -0.184405,  5.0, 0,    71 }, // Kensington Palace     -            
    {     40.5241,     -108.99,  5.0, 0,    72 }, // Steamboat Rock Colorado  -            
    {     41.7341,    -111.828,  5.0, 0,    73 }, // Logan Utah Temple     -            
    {     40.7705,    -111.892,  5.0, 0,    74 }, // Salt Lake City Temple  -            
    {     38.0982,     -78.487,  5.0, 0,    77 }, // Virginia Rowing       -            
    {     38.1108,    -78.4989,  5.0, 0,    78 }, // Rowenna River         -            
    {     19.4813,    -155.933,  5.0, 0,    79 }, // Hawaii Captain Cook monument  -            
    {     40.7515,    -73.9754,  5.0, 0,    84 }, // Chryslter Building    -            
    {      48.861,     2.33782,  5.0, 0,    85 }, // The Louvre            -            
    {     29.9766,     31.1311,  5.0, 0,    86 }, // Ghiza Pyramids        -            
    {     -33.857,     151.215,  5.0, 0,   127 }, // Sydney Opera House    -            
    {    -25.3437,     131.035,  5.0, 0,   128 }, // Uluru-Kata Tjuta National Park  -            
    {     35.2529,    -81.1579,  5.0, 0,   146 }, // Schiele Museum of Natural History  -            
    {     24.5542,     -81.794,  5.0, 0,   147 }, // Key West              -            
    {     8.15481,    -77.6917,  5.0, 0,   156 }, // Yaviza                -            
    {     7.72001,    -77.5615,  5.0, 0,   157 }, // Darian Gap            -            
    {     14.1303,     38.7197,  5.0, 0,   158 }, // Axum Tsion St. Mary (The Ark)  -            
};

inline uint32_t sorted_targets [NUM_TARGETS];


#endif
