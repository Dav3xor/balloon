typedef struct { //lat long in decimal degrees
    float lat;
    float lon;
    float distance;
    uint32_t priority;
} Target;

Target targets[] = {
    {39.9033, 116.3917, 0, 0}, //Tiananman Square 
    {51.5072, -0.1275, 0, 1}, //London 
    {48.8567, 2.3522, 0, 2}, //Paris 
};
