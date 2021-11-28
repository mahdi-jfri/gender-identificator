# Gender Identificator

Identify the gender of Instagram Persian users by their username. (the simplest peice of data given by Instagram in a public api along with their profile picture)
The algorithm is quite fast and estimated to predict in less than a second after being trained.

A dataset is gathered and labeled for this project exclusively.

## Motivation
In the world of advertising in social media, which almost has no shape and pattern, any data regarding targeted ads is precious. Knowing the portion of each gender following an Instagram page is a useful information for advertisers in most categories such as hair transplantation companies trying to reach to men and makeup product companies trying to reach to women.

## Work done
This project's data is gathered first by crawling some Persian pages in comments and creating a dataset of usernames and labelling them.
Then by crawling some Persian sites suggesting names and gathering different Persian names and their gender.

Then a vector is assigned to each username which shows if some name is "found" in that username. A fine-tuned SVM ran on this vectors shows fine results of about 85% accuracy on test dataset.

The vector creation of many usernames is implemented in `c++` instead of python to be efficient in time.
