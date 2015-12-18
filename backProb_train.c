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

#include "fann.h"

int main()
{
	char getNewAlg[80];

	unsigned int num_layers = 5;
	const unsigned 	int layers[6] = {784,100,100, 100, 10};
	const unsigned int num_neurons_hidden = 2;
	const float desired_error = (const float) 0.001;
	const unsigned int max_epochs = 100000;
	const unsigned int epochs_between_reports = 1000;
	struct fann_train_data *train_data = NULL;
	enum fann_train_enum training_algorithm = FANN_TRAIN_RPROP;

	train_data = fann_read_train_from_file("MINST_train.data");
	struct fann *ann = fann_create_standard_array(num_layers, layers);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	printf("Would you like to change the Algorithem (yes or no): ");
	if(scanf("%s",getNewAlg)==1);
	if(!strcmp(getNewAlg,"yes"))
	{
		int choice = 0;
		printf("Choice 1 FANN_TRAIN_RPROP, 2 FANN_TRAIN_BATCH, 3 FANN_TRAIN_QUICKPROP and 4 FANN_TRAIN_INCREMENTAL: ");
		if(scanf("%d",&choice));
		if(choice == 1)
		{
			// no need to do anything, by default, it is FANN_TRAIN_RPROP
		}
		else if(choice == 2)
		{
			training_algorithm = FANN_TRAIN_BATCH;
		}
		else if(choice == 3)
		{
			training_algorithm = FANN_TRAIN_QUICKPROP;
		}
		else
		{
			training_algorithm = FANN_TRAIN_INCREMENTAL;
		}

		if(choice > 1)
		{
			char newLearningRate[80];
			printf("The algorithm you choose can change the learning rate, would you like to change? (yes or no): ");
			if(scanf("%s",newLearningRate) == 1);
			if(!strcmp(newLearningRate,"yes"))
			{
				float learningRate = 0.0;
				printf("What is the new learning rate: ");
				if(scanf("%f",&learningRate))
					fann_set_learning_rate(ann,learningRate);
			}
		}
	}

	fann_set_training_algorithm(ann, training_algorithm);
	fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);


	fann_save(ann, "MINST.net");
	fann_destroy_train(train_data);
	fann_destroy(ann);

	return 0;
}
