#include"IsInFileNewRecord.h"

void IsInFileNewRecord(int i_level)
{

	std::fstream Records;
	Records.open("Records/RECORDS.txt", std::fstream::in);

	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	char buffer[128];
	strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);


	char temp;
	temp = buffer[3];
	buffer[3] = buffer[0];
	buffer[0] = temp;

	temp = buffer[4];
	buffer[4] = buffer[1];
	buffer[1] = temp;


	std::string PossibleNewRecord = "Reached level: " + std::to_string(i_level) + ": " + buffer;
	//PossibleNewRecord = "Reached level "+i_level+ ": ";


	////if there is not the file with records
	if (!Records.is_open())
	{
		Records.close();
		Records.open("Records/RECORDS.txt", std::fstream::out);

		Records.seekp(0, std::ios::beg);

		Records << PossibleNewRecord << '\n';

		Records.close();
		return;
	}
	
	///////////////////////////////////////////
	else
	{
		Myqueue<std::string> queueOfRecords;
		std::string Line;
		int count = 0;
		bool isPossibleRecordThere = false;

		while (!Records.eof())
		{
			Line = "";
			std::getline(Records, Line, '\n');

			if (Line.compare("") == 0) { continue; }

			queueOfRecords.push(Line);
		}

		Records.close();
		Records.open("Records/RECORDS.txt", std::fstream::out);
		Records.seekp(0, std::ios::beg);
			
		std::string ToFile;
			
			while (!queueOfRecords.isEmpty())
			{
				ToFile = queueOfRecords.front();
				if (ToFile.compare(PossibleNewRecord) > 0)
				{
					Records << ToFile << '\n';
					count++;
					queueOfRecords.pop();
				}
				else
				{
					Records << PossibleNewRecord << '\n';
					count++;
				isPossibleRecordThere= true;
					break;
				}
			}

			if(isPossibleRecordThere)
			while(count<AMOUNTRECORDS && !queueOfRecords.isEmpty() )
			{
				ToFile = queueOfRecords.front();
				Records << ToFile << '\n';
				count++;
				queueOfRecords.pop();
			}


			else
			{
				if (count == 0  || (  count>0 && count<AMOUNTRECORDS))
				{
					Records << PossibleNewRecord << '\n';
				}

			}
            

			Records.close();
			return;
	}
}