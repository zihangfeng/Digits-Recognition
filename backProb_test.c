/*
Fast Artificial Neural Network Library (fann)
Copyright (C) 2003-2016 Steffen Nissen (steffen.fann@gmail.com)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include "floatfann.h"

void printOutput(fann_type *output, int outputSize)
{
	int sizeOfOutput = outputSize;
	int i;
	for(i = 0; i < outputSize; i++)
	{
		printf("%f ",output[i]);
	}
	printf("\n");
}

// find the biggest index value
int biggestIndexValue(fann_type *output, int outputSize)
{

	int i;
	int index = 0;
	double currentLargestValue = output[0];
	for(i = 1; i < outputSize; i++)
	{
		if(output[i] > currentLargestValue)
		{
			currentLargestValue = output[i];
			index = i;
		}
	}

	return index;
}

int main()
{
	fann_type *calc_out;
	int dataSize = 0;
	int Num_Accurate = 0;
	struct fann *ann = fann_create_from_file("MINST.net");
	struct fann_train_data *data;
        if(!ann)
        {
                printf("Error creating ann --- ABORTING.\n");
                return 0;
        }

        printf("Testing network.\n");
        data = fann_read_train_from_file("MINST_test.data");
	dataSize = fann_length_train_data(data);
	int i = 0;
	for(i = 0; i < dataSize; i++)
	{
		calc_out = fann_run(ann, data->input[i]);
		//printOutput(calc_out, data->num_output);
		if(biggestIndexValue(calc_out,data->num_output) == biggestIndexValue(data->output[i],data->num_output))
		{
			Num_Accurate++;
		}
	}

	printf("Clearning up!\n");
	fann_destroy(ann);
	fann_destroy_train(data);

	printf("Result of Accuracy is: %f\n", (float)Num_Accurate/dataSize);
	return 0;
}
