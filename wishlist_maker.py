#parse text file with list of places and makes a c header file

import wikipediaapi

#set up wikipediaAPI agent
wiki = wikipediaapi.Wikipedia(user_agent='MyProjectName (merlin@example.com)', language='en')

#set up counter to represent the priority of a place
priority_counter = 0

with open('places.txt', 'r') as infile, open('wishlist.h', 'w') as outfile:

    outfile.write("typedef struct { //lat long in decimal degrees\n")
    outfile.write("    float lat;\n")
    outfile.write("    float lon;\n")
    outfile.write("    float distance;\n")
    outfile.write("    uint32_t priority;\n")
    outfile.write("} Target;\n\n")
    outfile.write("Target targets[] = {\n")

    for line in infile:
        place = line.strip()
        page = wiki.page(place)
        if page.exists() and page.coordinates:
            coords = wiki.coordinates(page)
            lat, lon = coords[0].lat, coords[0].lon

            outfile.write(f'    {{{lat:.4f}, {lon:.4f}, 0, {priority_counter}}}, //{place} \n')
            priority_counter += 1
        else:
            print(f"No page or coordinates found for {place}")


    outfile.write("};\n")
        
