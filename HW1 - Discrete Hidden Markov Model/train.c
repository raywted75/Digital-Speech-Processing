#include "hmm.h"

int main(int argc, char *argv[]) 
{

    FILE* file;

    //load the initial model 
    HMM hmm;
    loadHMM(&hmm, argv[2]);

    //iteration
    int iter = atoi(argv[1]);
    for(int i = 0; i < iter; i++)
    {
        //initialize 
        char sequence[MAX_SEQ];
        double sample_num = 0;
        double sum_initial[MAX_STATE] = {0};
        double sum_tran_n[MAX_STATE][MAX_STATE] = {0};
        double sum_tran_d[MAX_STATE] = {0};
        double sum_observ_n[MAX_OBSERV][MAX_STATE] = {0};
        double sum_observ_d[MAX_STATE] = {0};

        //for each iteration
        file = fopen(argv[3], "r");
        while(fscanf(file, "%s", sequence) != EOF)
        {
            int observ_len = strlen(sequence);
            sample_num += 1;

            //Forward Algorithm -> calculate alpha
            double alpha[MAX_SEQ][MAX_STATE] = {0};
            for(int t = 0; t < observ_len; t++)
            {
                for(int j = 0; j < hmm.state_num; j++)
                {
                    if(t == 0) 
                    { 
                        alpha[t][j] = hmm.initial[j] * hmm.observation[sequence[t] - 'A'][j]; 
                    }
                    else
                    {
                        for(int i = 0; i < hmm.state_num; i++)
                        {
                            alpha[t][j] += alpha[t-1][i] * hmm.transition[i][j];
                        }
                        alpha[t][j] *= hmm.observation[sequence[t]-'A'][j];
                    }
                    
                }
            }

            //Backward Algorithm -> calculate beta
            double beta[MAX_SEQ][MAX_STATE] = {0};
            for(int t = observ_len - 1; t >= 0; t--)
            {
                for(int i = 0; i < hmm.state_num; i++)
                {
                    if (t == observ_len - 1) 
                    { 
                        beta[t][i] = 1; 
                    }
                    else
                    {
                        for(int j = 0; j < hmm.state_num; j++)
                        {
                            beta[t][i] += hmm.transition[i][j] * hmm.observation[sequence[t+1] - 'A'][j] * beta[t+1][j];
                        }
                    } 
                }
            }

            //calculate gamma
            double gamma[MAX_SEQ][MAX_STATE] = {0};
            for(int t = 0; t < observ_len; t++)
            {
                double sum = 0;
                for(int i = 0; i < hmm.state_num; i++)
                {
                    gamma[t][i] = alpha[t][i] * beta[t][i];
                    sum += gamma[t][i];
                }

                //normalize
                for(int i = 0; i < hmm.state_num; i++)
                {
                    gamma[t][i] /= sum;
                }
            }

            //calculate epsilon
            double epsilon[MAX_SEQ][MAX_STATE][MAX_STATE] = {0};
            for(int t = 0; t < observ_len - 1; t++)
            {
                double sum = 0;
                for(int i = 0; i < hmm.state_num; i++)
                {
                    for(int j = 0; j < hmm.state_num; j++)
                    {
                        epsilon[t][i][j] += alpha[t][i] * hmm.transition[i][j] * hmm.observation[sequence[t+1] - 'A'][j] * beta[t+1][j];
                        sum += epsilon[t][i][j];
                    }
                }

                //normalize
                for(int i = 0; i < hmm.state_num; i++)
                {
                    for(int j = 0; j < hmm.state_num; j++)
                    {
                        epsilon[t][i][j] /= sum;
                    }
                }
            }

            //accumulate gamma and epsilon
            for (int i = 0; i < hmm.state_num; i++) 
            {
                sum_initial[i] += gamma[0][i];

                for (int t = 0; t < observ_len-1; t++) 
                {
                    sum_tran_d[i] += gamma[t][i];
                    for (int j = 0; j < hmm.state_num; j++)
                    {
                        sum_tran_n[i][j] += epsilon[t][i][j];
                    }
                }

                for (int t = 0; t < observ_len; t++) 
                {
                    sum_observ_d[i] += gamma[t][i];
                    sum_observ_n[sequence[t]-'A'][i] += gamma[t][i];
                }
            }
        }
        fclose(file);

        //Re-estimate HMM
        //calculate new initial prob
        for(int i = 0; i < hmm.state_num; i++)
        {
            hmm.initial[i] = sum_initial[i] / sample_num;
        }

        //calculate new transition prob
        for(int i = 0; i < hmm.state_num; i++)
        {
            for(int j = 0; j < hmm.state_num; j++)
            {
                hmm.transition[i][j] = sum_tran_n[i][j] / sum_tran_d[i];  
            }   
        }

        //calculate new observation prob
        for(int k = 0; k < hmm.observ_num; k++)
        {
            for(int j = 0; j < hmm.state_num; j++)
            {
                hmm.observation[k][j] = sum_observ_n[k][j] / sum_observ_d[j];
            }
        }
    }
    
    //save model
    file = fopen(argv[4], "w");
    dumpHMM(file, &hmm);
    fclose(file);
 
    return 0;
}