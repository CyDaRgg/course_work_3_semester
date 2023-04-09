#include"FillFileAfterRemove.h"
void FillFileAfterRemove(fstream& Records, MenuRecords& MenRec)
{
	Records.open("Records/RECORDS.txt", std::fstream::out);
	Records.seekp(0, std::ios::beg);

	std::string* tempRecords;
	tempRecords = MenRec.getRecords();

	for (int i = 0; i < AMOUNTRECORDS; i++)
	{

		if (tempRecords[i].compare(EMPTY_RECORD) == 0)
		{
			break;
		}
		Records << tempRecords[i] << '\n';
	}
}