#pragma once

namespace marxan {
    using namespace std;

    typedef struct spu
    {
        double amount; // amount of species in pu
        double prob; // optional field that does ???
        int spindex; // index/id of species
    } spu;

    //Separate output fields for multithreading 
    typedef struct spu_out
    {
        int clump;
        spu_out() { clump = 0; }
    } spu_out;

    typedef struct spusporder
    {
        double amount;
        int puindex;
    } spusporder;

    // type definitions for original Ian Ball data structures

    typedef struct spustuff
    {
        int id;
        int status;
        double xloc, yloc;
        double cost;
        double prob;
        int richness, offset, probrichness, proboffset;
    } spustuff;

    typedef struct spu_penalty
    {
        double penalty_add;
        double penalty_remove;
        double shortfall_add;
        double shortfall_remove;

        spu_penalty() : 
            penalty_add(0.0), 
            penalty_remove(0.0), 
            shortfall_add(0.0), 
            shortfall_remove(0.0)
        {}

        double get_penalty(int mode) const
        {
            if (mode == 1)
                return penalty_add;
            else
                return penalty_remove;
        }

        double get_shortfall(int mode) const
        {
            if (mode == 1)
                return shortfall_add;
            else
                return shortfall_remove;
        }

    } spu_penalty;

} // namespace marxan