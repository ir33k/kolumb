/* Kolumb - A program for generating random latitude and longitude
 * point pairs with Haversine distances calculated for each pair. */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>

enum file {
    DATA_JSON,
    DATA_F64,
    HSIN_JSON,
    HSIN_F64,
    INFO_TXT,
    _FILE_COUNT
};

void usage(char *arg0);
char *get_filename(char *prefix, enum file f);
void run(char *prefix, long long count, long long seed);
double haversine(double lon1, double lat1, double lon2, double lat2);
void write_json(FILE *fp);
void write_f64(FILE *fp);
void write_txt(FILE *fp);

/*********************************************************************
 * Implementation
 */

int
main(int argc, char **argv)
{
	if (argc < 3) {
		usage(argv[0]);
		errx(1, "Missing required arguments");
	}
	run(argv[1],
	    atoll(argv[2]),
	    argc > 3 ? atoll(argv[3]) : 0);
	return 0;
}

void
usage(char *arg0)
{
	printf("%s prefix count [seed]\n"
	       , arg0);
}

char *
get_filename(char *prefix, enum file f)
{
	static char filename[FILENAME_MAX] = "";
	char *suffix;
	switch (f) {
	case DATA_JSON: suffix = "data.json"; break;
	case DATA_F64:  suffix = "data.f64";  break;
	case HSIN_JSON: suffix = "hsin.json"; break;
	case HSIN_F64:  suffix = "hsin.f64";  break;
	case INFO_TXT:  suffix = "info.txt";  break;
	case _FILE_COUNT:
		/* Added for completion but not a real file so
		 * fallthrough to assertion. */
	default:
		assert(0);	/* Unreachable */
	}
	snprintf(filename, sizeof(filename), "%s%s", prefix, suffix);
	return filename;
}

void
run(char *prefix, long long count, long long seed)
{
	(void)count;	/* Unused param */
	(void)seed;	/* Unused param */
	int i;
	char *filename;
	FILE *fp;
	for (i = 0; i < _FILE_COUNT; i++) {
		filename = get_filename(prefix, i);
		if (!(fp = fopen(filename, "w"))) {
			err(1, "Failed to open file: %s", filename);
		}
		switch (i) {
		case DATA_JSON:
			write_json(fp);
			break;
		case DATA_F64:
			write_f64(fp);
			break;
		case HSIN_JSON:
			write_json(fp);
			break;
		case HSIN_F64:
			write_f64(fp);
			break;
		case INFO_TXT:
			write_txt(fp);
			break;
		default:
			assert(0);	/* Unreachable */
		}
		if (fclose(fp)) {
			err(1, "Failed to close file: %s", filename);
		}
	}
}

double
haversine(double lon1, double lat1, double lon2, double lat2)
{
#define degToRad(deg) ((deg) * M_PI / 180.0)
#define square(x) (pow((x),2))
	static const float earth_radius =  6372.8; /* that's an averrage - there is no one eart radius */
	double dlat  = degToRad(lat2 - lat1);
	double dlon  = degToRad(lon2 - lon1);
	double rlat1 = degToRad(lat1);
	double rlat2 = degToRad(lat2);
	double tmp = square(sin(dlat/2.0)) + cos(rlat1) * cos(rlat2) * square(sin(dlon/2.0));
	return earth_radius * 2.0 * asin(sqrt(tmp));
}

void
write_json(FILE *fp)
{
	(void)fp;	/* Unused param */
}

void
write_f64(FILE *fp)
{
	(void)fp;	/* Unused param */
}

void
write_txt(FILE *fp)
{
	(void)fp;	/* Unused param */
}
