//  Text Editor
//
//  Type some text and saves to a selected directory
//  Created by Daniel Eisterhold on 10/2/13.
//  Copyright (c) 2013 Daniel Eisterhold. All rights reserved.
//

#ifndef Text_Editor_main_h
#define Text_Editor_main_h

string createFile()
{
    //Location where the file has been created.
    string fileLocation;
    string fileName;
    string chosenFolder;
    int folderNumber;
    
    //Available locations the user can save the file
    const string desktop = "Desktop";
    const string documents = "Documents";
    const string downloads = "Downloads";
    const string extension = ".txt";
    
    //File Manipulator
    ofstream newFile;
    ifstream existingFile;
    
    do {
        do
        {
            //List the locations where the file can be stored
            cout<<"\nCreate File\n"<<"------------\n"<<"1. Desktop\n"<<"2. Documents\n"<<"3. Downloads\n"<<endl;
            //Get input from user of where to store the file
            cout<<"Please enter the number of the folder that you wish to save to: ";
            cin.clear();
            cin>>folderNumber;
            cin.clear();
            cin.ignore(1000, '\n');
            
        } while (folderNumber != 1 && folderNumber != 2 && folderNumber != 3);
        
        //Assign the correct file according to the users selections
        switch (folderNumber) {
            case 1:
                chosenFolder = desktop;
                break;
                
            case 2:
                chosenFolder = documents;
                break;
                
            case 3:
                chosenFolder = downloads;
                break;
                
            default:
                chosenFolder = documents;
                break;
        }
        
        //Ask for the file name.
        cout<<"\nPlease enter a name for the file that you wish to create: ";
        cin.clear();
        getline(cin,fileName);
        cin.clear();
        
        //Create the file directory
        fileLocation = directory + chosenFolder + "/"+ fileName + extension;
        //Test to see if file already exists
        existingFile.open(fileLocation.c_str());
        if(existingFile)
        {
            cout<<"The file already exists at: \""<<fileLocation<<"\""<<endl;
            existingFile.open(fileLocation.c_str());
        }
        else
        {
            newFile.open(fileLocation.c_str());
            cout<<"The file has been created at: \""<<fileLocation<<"\""<<endl;
        }
        
        if(!newFile)
        {
            cout<<"Invalid File Name! Please Try Again.";
        }
    } while (!newFile);
    
    return fileLocation;
}

string openFile()
{
    //Location where the file has been created.
    string fileLocation;
    string fileName;
    string chosenFolder;
    int folderNumber;
    
    //Available locations the user can save the file
    const string desktop = "Desktop";
    const string documents = "Documents";
    const string downloads = "Downloads";
    const string extension = ".txt";
    
    //File Manipulator
    ofstream newFile;
    ifstream existingFile;
    
    do {
        do
        {
            //List the locations where the file can be stored
            cout<<"\nOpen File\n"<<"------------\n"<<"1. Desktop\n"<<"2. Documents\n"<<"3. Downloads\n"<<"4. Cancel\n"<<endl;
            //Get input from user of where to store the file
            cout<<"Please enter the number of the folder that the file is saved in: ";
            cin.clear();
            cin>>folderNumber;
            cin.clear();
            cin.ignore(1000, '\n');
        } while (folderNumber != 1 && folderNumber != 2 && folderNumber != 3 && folderNumber != 4);
        
        //Assign the correct file according to the users selections
        switch (folderNumber)
        {
            case 1:
                chosenFolder = desktop;
                break;
                
            case 2:
                chosenFolder = documents;
                break;
                
            case 3:
                chosenFolder = downloads;
                break;
                
            case 4:
                return "0";
                break;
                
            default:
                chosenFolder = documents;
                break;
        }
        
        
        //Ask for the file name
        cout<<"\nPlease enter a name for the file that you wish to open: ";
        cin.clear();
        getline(cin,fileName);
        cout<<"\n";
        cin.clear();
        
        //Create the file directory
        fileLocation = directory + chosenFolder + "/"+ fileName + extension;
        
        //Test to see if file already exists
        existingFile.open(fileLocation.c_str());
        
        if(existingFile)
            {
            cout<<"The file at: \""<<fileLocation<<"\" has been opened."<<endl;
            existingFile.close();
            }
        else
            {
            cout<<"The file at: \""<<fileLocation<<"\" does not exist"<<endl;
            newFile.open(fileLocation.c_str());
                if (newFile)
                {
                    cout<<"The file has been created at: \""<<fileLocation<<endl;
                    newFile.close();
                }
                else
                {
                    cout<<"The file was unable to be opened or created!"<<endl;
                    return fileLocation;
                }
            
            }
    } while (!existingFile && !newFile);
    
    return fileLocation;
}

int writeToFile(string fileLocation)
{
    fstream outputFile;
    outputFile.open(fileLocation.c_str(),ios::in | ios::out);
    ifstream inputFile;
    inputFile.open(fileLocation.c_str(),ios::in | ios::out);
    
    if (outputFile)
    {
        //Clear out the user input
        cin.clear();
        
        string userInput;
        string fileContents;
        cout<<"Whatever you type will be saved to the file.\n"<<"To save the file and exit enter \"-1\""<<endl;
        
        //Read the contents already in the file
        while (!outputFile.eof())
        {
            getline(outputFile,fileContents);
            cout<<fileContents<<endl;
        }
        
        getline(cin,userInput);
        cin.clear();

        while (userInput != "-1")
        {
            outputFile<<userInput<<"\n";
            getline(cin,userInput);
        }
        
        outputFile.close();
        cout<<"The file has been saved."<<endl;
    }
    else
    {
        cout<<"Error. No file is currently open."<<endl;
    }
    return 0;
}
#endif
