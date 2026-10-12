#ifndef __WISHLIST_H__
#define __WISHLIST_H__

#define NUM_TARGETS 38
#define TARGET_APPROACHING 1
#define TARGET_DONE        2
#define TARGET_

typedef struct Target { // lat long in decimal degrees\n")
    float lat;
    float lon;
    float distance;
    uint16_t priority;
    uint16_t flags;
    uint32_t id;
} __attribute__((__packed__)) Target;

inline Target targets[] = { 
    {    0.696443,     2.03142, 0, 2, 0,     1 }, // Tiananman Square      -            
    {    0.898969, -0.00222529, 0, 5, 0,     2 }, // London                -            
    {     0.85271,   0.0410536, 0, 5, 0,     3 }, // Paris                 -            
    {    0.785397,    -2.14675, 0, 5, 0,     6 }, // Salem Oregon          -            
    {    0.794473,     -2.1412, 0, 5, 0,    10 }, // Portland Oregon       - Portland ( PORT-lənd) is the m 
    {    0.319395,    -1.13141, 0, 1, 0,    11 }, // Epstein Island        - Little Saint James, nicknamed  
    {    0.660607,    -2.08596, 0, 5, 0,    15 }, // Yosemite              - Yosemite National Park ( yoh-S 
    {    0.778416,    -1.92859, 0, 5, 0,    16 }, // yellowstone           - Yellowstone National Park is a 
    {    0.159174,     -1.3919, 0, 2, 0,    17 }, // panama canal          - The Panama Canal (Spanish: Can 
    {    0.488488,     1.51713, 0, 2, 0,    18 }, // Mount Everest         - Mount Everest (known in Nepali 
    {    0.626267,     1.33541, 0, 2, 0,    19 }, // K2                    - K2, also known as Mount Godwin 
    {    0.731993,    0.844362, 0, 5, 0,    29 }, // Caspian Sea Monster   -            
    {    0.852738,   0.0400441, 0, 5, 0,    44 }, // Paris Eifel Tower     -            
    {     0.59858,     2.30941, 0, 5, 0,    60 }, // Miyajima Island Japan  -            
    {    0.617281,     2.42142, 0, 5, 0,    61 }, // Mount Fuji            -            
    {     0.83004,     0.18761, 0, 5, 0,    67 }, // Neuschwanstein        -            
    {    0.851949,   0.0364526, 0, 5, 0,    68 }, // Versailles 1          -            
    {      0.8519,   0.0366599, 0, 5, 0,    69 }, // Versailles 2          -            
    {    0.851822,   0.0369584, 0, 5, 0,    70 }, // Versailles 3          -            
    {    0.728397,    -1.95176, 0, 5, 0,    73 }, // Logan Utah Temple     -            
    {    0.711578,    -1.95288, 0, 5, 0,    74 }, // Salt Lake City Temple  -            
    {    0.664939,    -1.36986, 0, 5, 0,    77 }, // Virginia Rowing       -            
    {    0.665158,    -1.37006, 0, 5, 0,    78 }, // Rowenna River         -            
    {    0.340013,    -2.72155, 0, 5, 0,    79 }, // Hawaii Captain Cook monument  -            
    {    0.372888,    -2.75675, 0, 5, 0,    83 }, // USS Arizona Memorial  -            
    {    0.711248,    -1.29111, 0, 5, 0,    84 }, // Chryslter Building    -            
    {    0.852784,   0.0408027, 0, 5, 0,    85 }, // The Louvre            -            
    {    0.523189,     0.54334, 0, 5, 0,    86 }, // Ghiza Pyramids        -            
    {   -0.590916,      2.6392, 0, 5, 0,   127 }, // Sydney Opera House    -            
    {   -0.442331,     2.28699, 0, 5, 0,   128 }, // Uluru-Kata Tjuta National Park  -            
    {    0.686485,    -1.33733, 0, 5, 0,   133 }, // Space Telescope Science Institute  -            
    {    0.685638,    -1.33709, 0, 5, 0,   134 }, // Baltimore Harbor      -            
    {    0.684423,    -1.33572, 0, 5, 0,   135 }, // Francis Scott Key Bridge  -            
    {    0.615279,    -1.41647, 0, 5, 0,   146 }, // Schiele Museum of Natural History  -            
    {    0.428551,    -1.42757, 0, 5, 0,   147 }, // Key West              -            
    {    0.142328,    -1.35598, 0, 5, 0,   156 }, // Yaviza                -            
    {     0.13474,     -1.3537, 0, 5, 0,   157 }, // Darian Gap            -            
    {    0.246621,    0.675786, 0, 5, 0,   158 }, // Axum Tsion St. Mary (The Ark)  -            
};

inline uint32_t sorted_targets [NUM_TARGETS];


#endif
