#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv)
{	
		char filename[255];
		int MIN_SCORE = 0;
		printf("argc=%d, argv[0]=%s", argc, argv[1]);
		if (argc == 2)
		{
				strcpy(filename, argv[1]);
		}
		if (argc == 3)
		{
				strcpy(filename, argv[2]);
				MIN_SCORE = atoi(argv[1]);
		}
		printf("%s", filename);
		FILE *fp = NULL;
		fp = fopen(filename, "r");

		if (fp == NULL)
				return -1;

		char * line = NULL;
		size_t len = 0;
		ssize_t read;

		char output[255];
		strcpy(output, strcat(filename, ".cut"));
		FILE *out = NULL;
		out = fopen(output, "w");
		while ((read = getline(&line, &len, fp)) != -1) {
				//printf("Retrieved line of length %zu:\n", read);
				//printf("%s", line);
				int i = 0;
				char *ln = line;
				// go to the 5th field
				//printf("%s", ln);
				for (i = 0; i < 4; i++)
				{
						ln = strchr(ln, '\t');
						if (ln == NULL)
								break;
						else
								ln = ln + 1;
				}
				if (ln == NULL)
				{
						fputs(line, out);
						continue;
				}

				char qualitystr[5];
				memcpy(qualitystr, ln, 5);
				i = 0;
				while(qualitystr[i] >= '0' && qualitystr[i] <= '9')
						i++;
				qualitystr[i] = '\0';

				int qualityscore = atoi(qualitystr);
				char *cpln = NULL;
				cpln = strdup(line);
				char *endstr = strstr(cpln, "NM:i:");
				if (endstr != NULL)
				{
						*endstr = '\n';
						*(endstr + 1) = '\0';
				}
				//printf("%s - %d\n", qualitystr, qualityscore);
				if (qualityscore >= MIN_SCORE)
				{
						fputs(cpln, out);			
				} else {
						fputs("\n", out);
				}
				free(cpln);

		}

		fclose(fp);
		fclose(out);
		if (line)
				free(line);

		return 0;
}
