#ifndef jaewoo_h
#define jaewoo_h


using namespace std;

void algorithm(int(*map)[5],int row,int col,char start_direction,char *direction,int (*direction_case)[2]) {


	map[0][4] = 1;
	int insert_value = 1;
	int length = 0;
	int row_ = 0;
	int col_ = 0;

	while (1) {

		int count2 = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (map[i][j] == insert_value) {

					if (i > 0) {
						if (map[i - 1][j] == 0)
							map[i - 1][j] = insert_value + 1;
						count2++;
					}

					if (i < 4) {
						if (map[i + 1][j] == 0)
							map[i + 1][j] = insert_value + 1;
						count2++;
					}

					if (j < 4) {
						if (map[i][j + 1] == 0)
							map[i][j + 1] = insert_value + 1;
						count2++;
					}

					if (j > 0) {
						if (map[i][j - 1] == 0)
							map[i][j - 1] = insert_value + 1;
						count2++;
					}
				}
			}
		}
		insert_value++;
		if (count2 == 0) 
			break;
	}

	direction_case[row_][0] = row;
	direction_case[row_++][1] = col;
	while (1) {


		if (row > 0) {
			if (map[row - 1][col] - map[row][col] == -1) {
				row = row - 1;	
				direction_case[row_][0] = row;
				direction_case[row_++][1] = col;

				if (start_direction == 'a') {
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				else if (start_direction == 'w') {
					direction[length++] = 'w';
				}
				else if (start_direction == 'd') {
					direction[length++] = 'a';
					direction[length++] = 'w';
				}
				else if (start_direction == 's') {
					direction[length++] = 'd';
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				start_direction = 'w';
				if (row == 0 && col == 4)
					break;
				//	cout << "(" << row << ',' << col << ")" << ">" << endl;
			}
		}
		if (row < 4) {
			if (map[row + 1][col] - map[row][col] == -1) {
				row = row + 1;
				direction_case[row_][0] = row;
				direction_case[row_++][1] = col;

				if (start_direction == 'a') {
					direction[length++] = 'a';
					direction[length++] = 'w';
				}
				else if (start_direction == 'w') {
					direction[length++] = 'd';
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				else if (start_direction == 'd') {
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				else if (start_direction == 's') {
					direction[length++] = 'w';
				}
				start_direction = 's';
				if (row == 0 && col == 4)
					break;
				//	cout << "(" << row << ',' << col << ")" << ">" << endl;
			}
		}
		if (col < 4) {
			if (map[row][col + 1] - map[row][col] == -1) {
				col = col + 1;
				direction_case[row_][0] = row;
				direction_case[row_++][1] = col;

				if (start_direction == 'a') {
					direction[length++] = 'd';
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				else if (start_direction == 'w') {
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				else if (start_direction == 'd') {
					direction[length++] = 'w';
				}
				else if (start_direction == 's') {
					direction[length++] = 'a';
					direction[length++] = 'w';
				}
				start_direction = 'd';
				if (row == 0 && col == 4)
					break;
				//	cout << "(" << row << ',' << col << ")" << ">" << endl;
			}
		}
		if (col > 0) {
			if (map[row][col - 1] - map[row][col] == -1) {
				col = col - 1;
				direction_case[row_][0] = row;
				direction_case[row_++][1] = col;

				if (start_direction == 'a') {
					direction[length++] = 'w';
				}
				else if (start_direction == 'w') {
					direction[length++] = 'a';
					direction[length++] = 'w';
				}
				else if (start_direction == 'd') {
					direction[length++] = 'd';
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				else if (start_direction == 's') {
					direction[length++] = 'd';
					direction[length++] = 'w';
				}
				start_direction = 'a';
				if (row == 0 && col == 4)
					break;
				//	cout << "(" << row << ',' << col << ")" << ">" << endl;
			}
		}


	}
	//cout << endl;
}
#endif