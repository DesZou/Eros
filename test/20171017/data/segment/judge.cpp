#include <math.h>
#include <stdio.h>
FILE *fscore,*freport,*fstd,*fin,*fout;
int main(int argc,char *argv[])
{
    fin=fopen(argv[1],"r");
    fout=fopen(argv[2],"r");
    fstd=fopen(argv[3],"r");
    //fopen(argv[4],"r");
    fscore=fopen(argv[5],"w");
    freport=fopen(argv[6],"w");
	double a,b;
	int td=0;
	while(fscanf(fstd,"%lf",&a)!=EOF)
	{
		fscanf(fout,"%lf",&b);
		if (b != b) {
			fprintf(fscore, "0");
			return 0;
		}
		td++;
		if(fabs(a-b)>1e-8&&(fabs(a-b)/a)>1e-8)
		{
		    fprintf(fscore,"0");
			fprintf(freport,"At the %d line:yourans: %.3lf  stdans: %.3lf",td,b,a);
		    return 0;
		}
	}
	fprintf(freport,"ok %d numbers",td);
	fprintf(fscore,"10");
	return 0;
}
    
