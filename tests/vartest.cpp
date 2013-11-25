#include "TecplotFile.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	TecplotFile tf(argv[1]);

	TecplotData data = tf.data();

	printf("Data title is %s", data.title().c_str());
}