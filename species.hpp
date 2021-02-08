#pragma once

#include <string>
#include <vector>

namespace marxan {
    using namespace std;

    extern double computeSepPenalty(int ival, int itarget);

    typedef struct sclumps
    {
        int clumpid;
        double amount;
        int occs;
        vector<int> head;
    } sclumps; /* Clump nodes for species Clump Structure */

    typedef struct sspecies
    {
        int name;
        int type;
        string sname;
        double target;
        double prop;
        int targetocc;
        double spf;
        double penalty;
        double rUserPenalty;
        double amount;
        double expected1D, expected2D, variance1D, variance2D;
        int occurrence;
        double sepdistance;
        int sepnum;
        int separation;
        int clumps;
        double target2;  // Only clumping species need this
        vector<sclumps> head;  // needed for clumping species
        int richness, offset;
        double Zscore1D, Zscore2D;
        double probability1D, probability2D;
        double ptarget1d, ptarget2d;

        //fileds for helping to compute penalty
        double fractionAmount;
        double shortFall;
        double tamount_add;
        double tamount_remove;
        double penalty_mult_spf;
        bool is_target;

        void update_penalty_components()
        {
            fractionAmount = 0.0;
            shortFall = 0.0;
            is_target = target != 0.0;

            if (target > amount && target != 0)
            {
                fractionAmount = (target - amount) / target;
                shortFall = target - amount;
            }
            
            // does this species have occurrence target?
            
            if (targetocc > 0)
            {
                if (targetocc > occurrence)
                    fractionAmount += (double)(targetocc - occurrence) / (double)targetocc;

                if (target && targetocc)
                    fractionAmount /= 2;
            }

            if (sepnum)
                fractionAmount += computeSepPenalty(separation, sepnum);

            tamount_add = 0.0;
            tamount_remove = 0.0;

            if (targetocc)
            {
                if((targetocc - occurrence - 1) > 0)
                    tamount_add = (double)(targetocc - occurrence - 1) /(double)targetocc;
                if ((targetocc - occurrence + 1) > 0)
                    tamount_remove = (double)(targetocc - occurrence + 1) / (double)targetocc;
            }

            penalty_mult_spf = penalty * spf;

        }

    }sspecies;


    typedef struct sgenspec
    {
        int type;
        int targetocc;
        double target;
        double target2;
        int sepnum;
        double sepdistance;
        double prop;
        double spf;
    } sgenspec;


} // namespace marxan