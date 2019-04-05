#include "hmm.h"

#define HMMNUM 5

int main(int argc, char *argv[])
{
    FILE* file = fopen(argv[2], "r");
    FILE* result = fopen(argv[3], "w");

    HMM hmms[HMMNUM];
    load_models(argv[1], hmms, HMMNUM);

    char sequence[MAX_SEQ];
    while(fscanf(file, "%s", sequence) != EOF)
    {
        int observ_len = strlen(sequence);
        double model_prob[HMMNUM] = {0};
        double highest_prob = 0;
        int highest_model = 0;

        //for each model
        for(int m = 0; m < HMMNUM; m++)
        {
            //calculate delta
            double delta[MAX_SEQ][MAX_STATE] = {0};
            for(int t = 0; t < observ_len; t++)
            {
                for(int j = 0; j < hmms[m].state_num; j++)
                {
                    if (t == 0) 
                    {
                        delta[t][j] = hmms[m].initial[j] * hmms[m].observation[sequence[t] - 'A'][j];
                    }
                    else
                    {
                        for(int i = 0; i < hmms[m].state_num; i++)
                        {
                            double product = delta[t-1][i] * hmms[m].transition[i][j];
                            if (product > delta[t][j]) 
                            {
                                delta[t][j] = product;
                            }
                        }
                        delta[t][j] *= hmms[m].observation[sequence[t]-'A'][j];
                    } 
                }
            }
            
            for(int i = 0; i < hmms[m].state_num; i++)
            {
                //find the state with the highest probability
                if (delta[observ_len-1][i] > model_prob[m]) 
                {
                    model_prob[m] = delta[observ_len-1][i];

                    //find the model with the highest probability
                    if (model_prob[m] > highest_prob) 
                    {
                        highest_prob = model_prob[m];
                        highest_model = m;
                    }
                }
            }
        }
        
        //write down the result
        fprintf(result, "model_0%d.txt %e\n", highest_model+1, highest_prob);     
    }

    fclose(file);
    fclose(result);

    return 0;
}