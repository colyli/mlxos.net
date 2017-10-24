#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PROG "find_friend"
void usage(void)
{
	fprintf(stderr, "\n\nUsage: %s [OPTION]... [male|female]\n", PROG);
	fprintf(stderr, "Search boy/girl friends with your requirement.\n"
		"\nHere are options for your query\n"
		"-a, --age             exact age\n"
		"-w, --weight          exact weight\n"
		"-c, --character       personal characters, please separate \n"
		"                      each option with comma\n"
		"    sweet                 always sweet smile\n"
		"    laborious             happy to do housework\n"
		"    smart                 of cause not too smart then you\n"
		"    slim                  perfect shape in common sense\n"
		"-e, --employed        if she or he has a job\n"
		"    <job name>            optional, if you also want to search\n"
		"                          her or his job\n"
		"-d, --dreamlover      extra conditions if she or he has dream-\n"
		"                      lover, separate each suboption with comma\n"
		"    name=<name>           name of dreamlover\n"
		"    weight=<weight>       weight of dreamlover\n"
		"    height=<height>       height of dreamlover\n"
		"-l, --local           only search your own school\n"
		"-f, --flagtest        flag test only\n");
	exit(EXIT_FAILURE);
}

int testflag = (int)'0';

struct option long_options[] =
{
	{"help",        no_argument,       NULL,      'h'},
	{"age",         required_argument, NULL,      'a'},
	{"weight",      required_argument, NULL,      'w'},
	{"character",   required_argument, NULL,      'c'},
	{"employed",    optional_argument, NULL,      'e'},
	{"dreamlover",  required_argument, NULL,      'd'},
	{"local",       no_argument,       NULL,      'l'},
	{"flagtest",    no_argument,       &testflag, 'T'},
	{0,             0,                 0,          0 }
};

char *short_options = "a:w:c:e::d:lTh";

typedef enum
{
	CH_SWEET = 0,
	CH_LABORIOUS,
	CH_SMART,
	CH_SLIM,
	CH_END
}character_t;

typedef enum
{
	DR_NAME = 0,
	DR_WEIGHT,
	DR_HEIGHT,
	DR_END
}dreamlover_t;

char * const ch_options[] =
{
	[CH_SWEET] = "sweet",
	[CH_LABORIOUS] = "laborious",
	[CH_SMART] = "smart",
	[CH_SLIM] = "slim",
	[CH_END] = NULL
};

char * const dr_options[] =
{
	[DR_NAME] = "name",
	[DR_WEIGHT] = "weight",
	[DR_HEIGHT] = "height",
	[DR_END] = NULL
};

int main(int argc, char *argv[])
{
	int c, option_index;
	int invalid_opt = 0;
	character_t ch;
	dreamlover_t dr;
	char *subopts, *value;

	while (1)
	{
		option_index = 0;
		c = getopt_long(argc, argv, short_options, long_options, &option_index);
		if (c < 0)
			break;
		switch (c)
		{
			case 0: /* option found and flag is not NULL */
				printf("opiton found with non-NULL flag\n"
					"        option index: %d\n"
					"        option name: %s\n"
					"        option flag: %d (testflag: %d)\n"
					"        short option: %c\n",
					option_index,
					long_options[option_index].name,
					*(long_options[option_index].flag),
					testflag,
					long_options[option_index].val);
				break;
			case 'h':
				usage();
				break;
			case 'a':
				printf("-a,--age option found, value: %s\n",
					optarg);
				break;
			case 'w':
				printf("-w,--weight option found, value: %s\n",
					optarg);
				break;
			case 'c':
				printf("-c,--character option found, value: %s\n",
				optarg);
				subopts = optarg;
				while(*subopts != '\0')
				{
					value = "";
					ch = getsubopt(
						&subopts, ch_options, &value);
					switch(ch)
					{
						case CH_SWEET:
							printf("        sweet "
							 "option found\n");
							break;
						case CH_LABORIOUS:
							printf("        laborious "
							 "option found\n");
							break;
						case CH_SMART:
							printf("        smart "
							 "option found\n");
							break;
						case CH_SLIM:
							printf("        slim "
							 "option found\n");
							break;
						default:
							printf("        %s: "
							 "invalid option\n",
							 subopts);
							 invalid_opt = 1;
							break;
					}
				}
				if (invalid_opt)
					usage();
				break;
			case 'e':
				printf("-e,--employed option found, ");
				if (!optarg)
					printf("no exact job required.\n");
				else
					printf("requried job: %s\n", optarg);
				break;
			case 'd':
				printf("-d,--dreamlover option found, value: %s\n", optarg);
				subopts = optarg;
				while(*subopts != '\0')
				{
					value = "";
					dr = getsubopt(
						&subopts, dr_options, &value);
					switch (dr)
					{
						case DR_NAME:
							printf("        name: "
							 "%s\n", value);
							break;
						case DR_WEIGHT:
							printf("        weight: "
							 "%s\n", value);
							break;
						case DR_HEIGHT:
							printf("        height: "
							 "%s\n", value);
							break;
						default:
							printf("        %s: "
							 "invalid option\n",
							 value);
							invalid_opt = 1;
							break;
					}
				}
				if (invalid_opt)
					usage();
				break;
			case 'l':
				printf("-l,--local option found, search friend in your own school.\n");
				break;
			case 'T':
				printf("-T,--flagtest option found, flag value: %d\n", testflag);
				break;
			default:
				usage();
		}
	}
	
	if (optind != (argc - 1))
		usage();
	printf("sex value: ");
	if (!strcmp(argv[optind], "male"))
		printf("male\n");
	else if (!strcmp(argv[optind], "female"))
		printf("female\n");
	else
	{
		printf("unknow sexual orientation\n");
		usage();
	}

	return 0;
}
