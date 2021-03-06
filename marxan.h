// declare structures, types, and some variables of type
// predefine functions that are called before they're defined

#define DebugFree(x)
#ifndef mainheaderfile
#define mainheaderfile

    double delta;

    // type definitions for sparse matrix optimisations data structures
    typedef struct binsearch
    {
        int name;
        int index;
    } typebinsearch;

    typebinsearch *PULookup;
    typebinsearch *SPLookup;

    typedef struct spu
    {
        double amount;
        double prob;
        int clump;
        int spindex;
    } typepu;

    typepu *SM;

    typedef struct spusporder
    {
        double amount;
        int puindex;
    } typepusporder;

    typepusporder *SMsporder;

    // type definitions for original Ian Ball data structures

    typedef struct spustuff
    {
        int id;
        int status;
        double xloc,yloc;
        double cost;
        double prob;
        int richness,offset,probrichness,proboffset;
    } typespu;

    typespu *pu;

    typedef struct scost
    {
        double total;
        int pus;
        double connection;
        int missing;
        double penalty;
        double cost;
        double threshpen;
        double shortfall;
        double probability1D;
        double probability2D;
    } typecost;

    typecost reserve,change,debugcost;

    typedef struct sspecies
    {
        int name;
        int type;
        char *sname;
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
        struct sclumps *head;  // needed for clumping species
        int richness,offset;
        double Zscore1D, Zscore2D;
        double probability1D, probability2D;
        double ptarget1d, ptarget2d;
    }typesp;

    typesp *spec;

    /* Connectivity Structure. Fixed connectivity number. Should replace with link list! */
    struct sneighbour
    {
        int nbr;
        double cost;
        struct sneighbour *next;
        int connectionorigon;
    } *debugnbr;

    typedef struct sconnections
    {
        struct sneighbour *first;
        double fixedcost;
        int nbrno;
    }typeconnection;

    typeconnection *connections;

    struct sclumppu
    {
      int puid;
      struct sclumppu *next;
    };

    struct sclumps
    {
      int clumpid;
      double amount;
      int occs;
      struct sclumppu *head;
      struct sclumps *next;
    }; /* Clump nodes for species Clump Structure */

    typedef struct sanneal
    {
        long int Titns;
        long int iterations;
        long int Tlen;
        double Tinit;    /* Initial Temperature */
        double Tcool;    /* Cooling Factor */
        double temp; /* Current Temperature */
        double tempold;
        int type;    /* Type of annealing. 0 = none, 1 = fixed, 2 = adaptive */
        double sigma; /*Used in adaptive annealing */
        double sum; /* Used in adaptive annealing */
        double sum2; /* used in adaptive annealing */
    } typeanneal; /* Annealing Control handler */

    typeanneal anneal;

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
    } typegenspec;

    typedef struct sfname
    {
        char *inputdir;
        char *outputdir;
        char *specname;
        char *puname;
        char *puvsprname;
        char *matrixspordername;
        char *connectionname;
        char *blockdefname;
        char *bestfieldname;
        char *connectionfilesname;
        char *rbinarypath;
        char *penaltyname;
        int savebest;
        int saverun;
        int savesum;
        int savesen;
        int savespecies;
        int savesumsoln;
        int savelog;
        int savesnapsteps;
        int savesnapchanges;
        int savesnapfrequency;
        int savepenalty;
        int savetotalareas;
        int savedebugtracefile;
        int savesolutionsmatrix;
        int solutionsmatrixheaders;
        int saveannealingtrace;
        int annealingtracerows;
        int saveitimptrace;
        int itimptracerows;
        int saverichness;
        int savespec;
        int savepu;
        int savepuvspr;
        int savematrixsporder;
        int rexecutescript;
        int rimagetype;
        int rimagewidth;
        int rimageheight;
        int rimagefontsize;
        int rclustercount;
    } typefname;

    typefname fnames;

    typedef struct srunoptions
    {
        int CalcPenaltiesOn;
        int HeuristicOn;
        int ThermalAnnealingOn;
        int QuantumAnnealingOn;
        int ItImpOn;
    } typerunopts;

    typerunopts runoptions;

    struct slink
    {
        int id;
        struct slink *next;
    };

    typedef struct iimp
    {
        double randomfloat;
        int puindex;
    } typeiimp;

void addReserve(int puno,struct spustuff pu[],int R[]);
void computeSpecProp(int spno,typesp spec[],int puno,struct spustuff pu[],struct spu SM[]);
void setBlockDefinitions(int gspno,int spno,int puno,struct sgenspec gspec[], struct sspecies spec[],struct spustuff PU[], struct spu SM[]);
void setDefaultTargets(int spno, struct sspecies spec[]);
void setDefaultRunOptions(int runopts, struct srunoptions *runoptions);
int computePenalties(int puno,int spno,struct spustuff pu[],struct sspecies spec[],
                     struct sconnections connections[],struct spu SM[],int PUtemp[],int aggexist,double cm,int clumptype);
int computePenaltiesOptimise(int puno,int spno,struct spustuff pu[],struct sspecies spec[],
                             struct sconnections connections[],struct spu SM[],struct spusporder SMsp[],
                             int PUtemp[],int aggexist,double cm,int clumptype);


double ConnectionCost1(int ipu,struct spustuff pu[],struct sconnections connections[],double cm);
double computePlanningUnitValue(int ipu,struct spustuff pu[],struct sconnections connections[],double cm);
double ConnectionCost2(int ipu,struct sconnections connections[],int R[],int imode,int imode2,double cm);
void computeConnectivityIndices(double *rConnectivityTotal,double *rConnectivityIn,
                                double *rConnectivityEdge,double *rConnectivityOut,
                                int puno,int *R,typeconnection connections[]);
void computeReserveValue(int puno,int spno,int R[],struct spustuff pu[],
                         struct sconnections connections[],struct spu SM[],
                         double cm, struct sspecies spec[],int aggexist,struct scost *reserve,int clumptype);
void initialiseReserve(int puno,double prop, int R[]);
void computeChangeScore(int iIteration,int ipu,int spno,int puno,struct spustuff pu[],struct sconnections connections[],
                        struct sspecies spec[],struct spu SM[],int *R,double cm,int imode,
                        struct scost *change, struct scost *reserve,double costthresh,double tpf1, double tpf2,
                        double timeprop,int clumptype);
double computeSpeciesPlanningUnitPenalty(int ipu,int isp,struct sspecies spec[],struct spustuff pu[], struct spu SM[],int imode);
void doChange(int ipu,int puno,int *R,struct scost *reserve,struct scost change,
              struct spustuff pu[],struct spu SM[],struct sspecies spec[],struct sconnections connections[],
              int imode,int clumptype);

int computeRepresentationMISSLEVEL(int spno,struct sspecies spec[],double misslevel,double *shortfall,double *rMinimumProportionMet);
void displayValueForPUs(int puno, int spno,int R[],struct scost reserve,
                        struct sspecies spec[],double misslevel);
void TimePassed(void);
void PauseProg(void);
void PauseExit(void);

#endif
#ifndef annealingheader
#define annealingheader


void initialiseConnollyAnnealing(int puno,int spno,struct spustuff pu[],typeconnection connections[],typesp spec[],
                                 struct spu SM[],double cm, struct sanneal *anneal,int aggexist,
                                 int R[],double prop,int clumptype,int irun);
void initialiseAdaptiveAnnealing(int puno,int spno,double prop,int *R,struct spustuff pu[],struct sconnections connections[],
                                 struct spu SM[],double cm,struct sspecies spec[],int aggexist,struct sanneal *anneal,int clumptype);
void thermalAnnealing(int spno, int puno, struct sconnections connections[],int R[], double cm,
                      typesp *spec, struct spustuff pu[], struct spu SM[], struct scost *change, struct scost *reserve,
                      long int repeats,int irun,char *savename,double misslevel,
                      int aggexist,double costthresh, double tpf1, double tpf2,int clumptype);
void quantumAnnealing(int spno, int puno, struct sconnections connections[],int R[], double cm,
                      typesp *spec, struct spustuff pu[], struct spu SM[], struct scost *change, struct scost *reserve,
                      long int repeats,int irun,char *savename,double misslevel,
                      int aggexist,double costthresh, double tpf1, double tpf2,int clumptype);
#endif

#ifndef clumpingheader
#define clumpinheader

void ClearClump(int isp,struct sclumps *target,struct spustuff pu[],
                struct spu SM[]);
int ClumpCut(int isp,struct spustuff pu[],
        struct sspecies spec[],struct sclumps *clump,
        struct sclumppu *clumppu,struct sconnections connections[],struct spu SM[],
        double *totalamount,int *totalocc,
        int *iseparation, int imode,int clumptype);
void SetSpeciesClumps(int puno,int R[],struct sspecies spec[],struct spustuff pu[],
                      struct spu SM[],struct sconnections connections[],int clumptype);
void SpeciesAmounts4(int isp,struct sspecies spec[],int clumptype);
void ClearClumps(int spno,struct sspecies spec[],struct spustuff pu[], struct spu SM[]);
struct sclumps *AddNewClump(int isp,int ipu,struct sspecies spec[],struct spustuff pu[], struct spu SM[]);
void AddNewPU(int ipu,int isp,struct sconnections connections[],struct sspecies spec[],struct spustuff pu[],
              struct spu SM[], int clumptype);
void RemPu(int ipu, int isp,struct sconnections connections[], struct sspecies spec[],struct spustuff pu[],
           struct spu SM[],int clumptype);
int RemClumpCheck(struct sclumps *pclump,struct spustuff pu[]);

int CalcPenaltyType4(int isp,int puno, struct spu SM[],struct sconnections connections[],
    struct sspecies spec[],struct spustuff pu[],double cm,int clumptype);
double PartialPen4(int isp,double amount, struct sspecies spec[],int clumptype);
double ValueAdd(int isp,int ipu,int puno, int R[],struct sconnections connections[],struct spustuff pu[],
                struct spu SM[],struct sspecies spec[],int clumptype);
double ValueRem(int ipu,int isp,struct sspecies spec[],struct sconnections connections[],
                struct spustuff pu[],struct spu SM[],int clumptype);
double NewPenalty4(int ipu,int isp,int puno,struct sspecies spec[],struct spustuff pu[],struct spu SM[],
             int R[],struct sconnections connections[],int imode,int clumptype);

#endif

#ifndef fileinheader
#define fileinheader

struct snlink{char *name; struct snlink *next;};

/* Parmtypes */
#define NOTYPE 0
#define INTEGER 1
#define LONGINT 2
#define REAL 3
#define DOUBLE 4
#define STRING 5

struct snlink *storeFieldName(char **varlist,int numvars,char *sVarName,
    struct snlink *head,char *fname);

int NameToPUID(int puno,int name, struct spustuff pu[]);
int NameToSPID(int spno,int name,typesp spec[]);

void readInputOptions(double *cm,double *prop,struct sanneal *anneal,
                      int *iseed,
                      long int *repeats,char savename[],struct sfname *fname,char filename[],
                      int *runopts,double *misslevel,int *heurotype,int *clumptype,
                      int *itimptype, int *verb,
                      double *costthresh,double *tpf1,double *tpf2);

int LoadPuDat(int *puno,struct spustuff *pu[],struct sfname fnames);
int LoadSpecDat(int *spno,struct sspecies *spec[],struct sfname fnames);
int ReadGenSpeciesData(int *gspno,struct sgenspec *gspec[],struct sfname fnames);
int DumpAsymmetricConnectivityFile(int puno,struct sconnections connections[],struct spustuff pu[],struct sfname fnames);
int readConnections(int puno,struct sconnections connections[],struct spustuff pu[],
                    struct binsearch PULookup[],struct sfname fnames);

void ReadPUVSPFile22(int puno,int spno,struct spu SM[],struct spustuff pu[],
    typesp spec[],struct sfname fnames);
void ReadPUVSPFileTable(FILE *infile, int puno,int spno,struct spu SM[],struct spustuff pu[],
    typesp spec[]);

void readPenalties(typesp spec[],int spno,struct sfname fnames,struct binsearch SPLookup[]);
void applyUserPenalties(typesp spec[],int spno);

// functions for Matt's Big O notation optimisation
void readSparseMatrix(int *iSMSize, struct spu *SM[], int puno, int spno, struct spustuff PU[],
                      struct binsearch PULookup[],struct binsearch SPLookup[],
                      struct sfname fnames);
void writeSparseMatrix(int iSMno,int puno, struct spustuff PU[], struct sspecies spec[], struct spu SM[],struct sfname fnames);
void readSparseMatrixSpOrder(int *iSMSize, struct spusporder *SM[], int puno, int spno,
                             struct binsearch PULookup[],struct binsearch SPLookup[],// typesp spec[],
                             struct sfname fnames);
void writeBinarySearchArrays(char *sName,struct sfname fnames, int puno, int spno, struct binsearch PULookup[],
                             struct binsearch SPLookup[]);

void computeBinarySearch(int puno, int spno, struct spustuff PU[], typesp spec[],
                         struct binsearch *PULookup[], struct binsearch *SPLookup[]);
int binarySearchPuIndex(int puno,int name, struct binsearch PULookup[]);
int binarySearchSpecIndex(int spno,int name, struct binsearch SPLookup[]);
int returnIndexSpecAtPu(struct spustuff PU[], struct spu SM[], int iPUIndex, int iSpecIndex);
double returnAmountSpecAtPu(struct spustuff PU[], struct spu SM[], int iPUIndex, int iSpecIndex);
int rtnClumpSpecAtPu(struct spustuff PU[], struct spu SM[], int iPUIndex, int iSpecIndex);
void setClumpSpecAtPu(struct spustuff PU[], struct spu SM[], int iPUIndex, int iSpecIndex, int iSetClump);
void appendTraceFile(char sMess[],...);

#endif

#ifndef spexioheader
#define spexioheader
void SaveSeed(int iseed);

#endif

#ifndef heuristicheader
#define heuristicheader


double GreedyPen(int ipu, int puno, int spno, typesp spec[],int R[],struct spustuff pu[],
                 struct spu SM[],int clumptype);
double GreedyScore(int ipu,int puno,int spno, typesp *spec,struct spu SM[],struct sconnections connections[],
                   int R[],struct spustuff pu[],double cm,int clumptype);
void SetRareness(int puno, int spno, double Rare[],int R[],struct spustuff pu[],struct spu SM[]);
double RareScore(int isp,int ipu,int puno,typesp spec[],struct spu SM[], int R[],
    struct sconnections connections[], struct spustuff pu[], double cm,int clumptype);
double MaxRareScore(int ipu,int puno,struct sspecies spec[],struct spu SM[],
    int R[],struct sconnections connections[],struct spustuff pu[],double cm,double Rare[],int clumptype);
double BestRareScore(int ipu,int puno,struct sspecies spec[],struct spu SM[],
    int R[],struct sconnections connections[],struct spustuff pu[],double cm,double Rare[],int clumptype);
double AveRareScore(int ipu,int puno,struct sspecies spec[],struct spu SM[],
    int R[],struct sconnections connections[],struct spustuff pu[],double cm,double Rare[],int clumptype);
double SumRareScore(int ipu,int puno,struct sspecies spec[],struct spu SM[],
    int R[],struct sconnections connections[],struct spustuff pu[],double cm,double Rare[],int clumptype);
void SetAbundance(int puno,double Rare[],struct spustuff pu[],struct spu SM[]);
double Irreplaceability(int ipu,int isp, double Rare[],struct spustuff pu[],struct spu SM[],typesp *spec);
double ProdIrr(int ipu,double Rare[],struct spustuff pu[],struct spu SM[],typesp *spec);
double SumIrr(int ipu,double Rare[],struct spustuff pu[],struct spu SM[],typesp *spec);
void Heuristics(int spno,int puno,struct spustuff pu[],struct sconnections connections[],
        int R[], double cm,typesp *spec,struct spu SM[], struct scost *reserve,
        double costthresh, double tpf1,double tpf2, int imode,int clumptype);

#endif

#ifndef itimpheader
#define itimpheader

struct slink* ItImpDiscard(int ichoice, struct slink *list, struct slink **discard);
struct slink* ItImpUndiscard(struct slink *list, struct slink **discard);
int FindSwap( struct slink **list,double targetval,int itestchoice,int puuntried,
             int puno,int spno,struct spustuff pu[], struct sconnections connections[],
             struct sspecies spec[],struct spu SM[],
             int R[], double cm, struct scost *reserve, struct scost *change,
             double costthresh, double tpf1, double tpf2, int clumptype);
void iterativeImprovement(int puno,int spno,struct spustuff pu[], struct sconnections connections[],
                          struct sspecies spec[],struct spu SM[],int R[], double cm,
                          struct scost *reserve,struct scost *change,double costthresh,double tpf1, double tpf2,
                          int clumptype,int irun,char *savename);

#endif

#ifndef randomheader
#define randomheader

float returnRandomFloat(void);
void initialiseRandomSeed(int iSeed);
int returnRandom (int num);


#endif

#ifndef outputheader
#define outputheader

void displayStartupMessage(void);
void displayShutdownMessage(void);

void SetVerbosity(int verb);

void displayErrorMessage(char sMess[],...);
void displayWarningMessage(char sMess[],...);

void displayProgress(char sMess[],...);
void displayProgress1(char sMess[],...);
void displayProgress2(char sMess[],...);
void displayProgress3(char sMess[],...);

void displayTimePassed(void);

void SetLogFile(int my_savelog, char* my_savelogname);

#endif

#ifndef sepheader
#define sepheader

typedef struct sseplist{
    int size;
    struct slink *head,*tail;
} typeseplist;


double SepPenalty(int ival, int itarget);
int ValidPU(int ipu,int isp,struct sclumps *newno,struct sspecies spec[],struct spustuff pu[],
            struct spu SM[],int imode);
int CheckDistance(int i, int j,struct spustuff pu[],double squaretarget);
int CountSeparation(int isp,struct sclumps *newno,
    struct spustuff pu[],struct spu SM[],typesp spec[],int imode);
struct slink *makelist(int isp,int inpu, int puno,int R[],struct sclumps *newno,struct sspecies spec[],
                       struct spustuff pu[],struct spu SM[],int imode);
int SepDealList(struct slink *head, typeseplist *Dist,struct spustuff *pu,
        struct sspecies spec[],int first,int sepnum,double targetdist,int isp);
int CountSeparation2(int isp,int ipu,struct sclumps *newno,int puno,int R[],
    struct spustuff pu[],struct spu SM[],typesp spec[],int imode);

void CheckDist(struct sseplist *Dist,int sepnum);

#endif

double probZUT(double z);
double probZLT(double z);

void ComputeP_AllPUsSelected_1D(char savename[],int puno,int spno,struct spustuff pu[],struct spu SM[],struct sspecies spec[]);
void ComputeP_AllPUsSelected_2D(char savename[],int puno,int spno,struct spustuff pu[],struct spu SM[],struct sspecies spec[]);
double ChangeProbability1D(int iIteration, int ipu, int spno,int puno,struct sspecies spec[],struct spustuff pu[],struct spu SM[],int imode);
double ChangeProbability2D(int iIteration, int ipu, int spno,int puno,struct sspecies spec[],struct spustuff pu[],struct spu SM[],int imode);
double Probability(int ipu, int spno,int puno,struct sspecies spec[],struct spustuff pu[],struct spu SM[]);
void ReturnProbabilityAmounts1D(double ExpectedAmount1D[],double VarianceInExpectedAmount1D[],int ipu,
                                int puno,struct spustuff pu[],struct spu SM[]);
void ReturnProbabilityAmounts2D(double ExpectedAmount2D[],double VarianceInExpectedAmount2D[],int ipu,
                                int puno,struct spustuff pu[],struct spu SM[]);
double ComputeProbability1D(double ExpectedAmount1D[],double VarianceInExpectedAmount1D[],
                            int spno,struct sspecies spec[]);
double ComputeProbability2D(double ExpectedAmount2D[],double VarianceInExpectedAmount2D[],
                            int spno,struct sspecies spec[]);
void createDebugFile(char sFileName[],char sHeader[],struct sfname fnames);
void appendDebugFile(char sFileName[],char sLine[],struct sfname fnames);
void writePenalty(int spno,struct sspecies spec[],char savename[],int iOutputType);
void writePenaltyPlanningUnits(int puno,struct spustuff pu[],int Rtemp[],char savename[],int iOutputType);
void writeSpec(int spno,struct sspecies spec[],char savename[]);

void createSolutionsMatrix(int puno,struct spustuff pu[],char savename_ism[],int iOutputType,int iIncludeHeaders);

void writeSlaveSyncFileRun(int iSyncRun);
void slaveExit(void);

