#include <stdio.h>
#include "map.h"

int main()
{
    map* map = map_init();
    map->push(map, "name", "XXIV");
    printf("%s\n", map->get(map, "name"));
    printf("%s\n", map->get_key(map, "XXIV"));
    map_clean(map);
    return 0;
}