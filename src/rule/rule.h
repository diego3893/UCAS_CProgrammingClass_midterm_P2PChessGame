#ifndef RULE_H
#define RULE_H

typedef struct{
    int dx;
    int dy;
}DeltaPair;

#define DELTA_RIGHT ((DeltaPair){1, 0})   
#define DELTA_DOWN ((DeltaPair){0, -1})  
#define DELTA_LEFT ((DeltaPair){-1, 0}) 
#define DELTA_UP ((DeltaPair){0, 1}) 
#define DELTA_UPRIGHT ((DeltaPair){1, 1}) 
#define DELTA_UPLEFT ((DeltaPair){-1, 1}) 
#define DELTA_DOWNLEFT ((DeltaPair){-1, -1})
#define DELTA_DOWNRIGHT ((DeltaPair){1, -1})

#endif 