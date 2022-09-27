#include <stdio.h>
#include <string.h>

#include <list>

using namespace std;

list<unsigned char> mask_list, raw_list;


int main(int argc, char **argv)
{
	FILE *fp_in = fopen(argv[1], "rb");
	FILE *fp_out = fopen(argv[2], "wb");

	if (!fp_in) {
		printf("can't open file %s\n", argv[1]);
		return -1;
	}

	if (!fp_out) {
		printf("can't open file %s\n", argv[1]);
		return -1;
	}


	unsigned char mask = 0;
	int mask_count = 0;
	int size = 0;


	while(1) {
		unsigned char ch = fgetc(fp_in);
		if (feof(fp_in)) break;


		mask <<= 1;
		if (ch == 0) {
			mask |= 0;
		}
		else {
			mask |= 1;

			raw_list.push_back(ch);
		}


		mask_count++;
		if (mask_count == 8) {
			mask_list.push_back(mask);

			mask_count = 0;
			mask = 0;
		}


		size++;
	}


	if (mask_count > 0) {
		printf("warning: mask count %d // total size %x\n", mask_count, size);

		while (mask_count < 8) {
			mask <<= 1;
			mask |= 0;

			mask_count++;
		}

		mask_list.push_back(mask);
	}


	//fwrite(&size, 1, 2, fp_out);

	while(mask_list.size() > 0) {
		unsigned char ch = mask_list.front();
		mask_list.pop_front();


		fputc(ch, fp_out);
	}

	while(raw_list.size() > 0) {
		unsigned char ch = raw_list.front();
		raw_list.pop_front();


		fputc(ch, fp_out);
	}


	fclose(fp_in);
	fclose(fp_out);
}
