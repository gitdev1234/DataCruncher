/**
 * DataCruncher.cpp
 * Purpose: implements class DataCruncher
 *
 * @author Wall.Of.Death
 * @version 2.2
 */

#include "DataCruncher.h"

/* --- operators --- */
double& DataCruncher::operator [](int index_) {
    return vData[index_];
}

/* --- load / save --- */

/**
 * DataCruncher::loadFromFile
 * @brief loads file to current vector data
 * @param path_ path of file
 * @param separator_ string which is used as separator in the csv-file, not used for binary files
 * @return returns true, if file was sucessfully loaded, otherwise false
 *
 * if suffix of path_ is "csv" file is interpreted as a csv-file
 * if suffix of path_ is "" vector data is not loaded, function returns false
 * if suffix of path_ is not "" and not "csv" file is interpreted as binary file
 *
 * NOTE : is does not matter, if suffix is uppercase or lower case, or anything in between
 */
bool DataCruncher::loadFromFile(const string &path_, char separator_) {
    return ( loadFromCSVFile(path_,separator_) || loadFromBinaryFile(path_) );
}

/**
 * DataCruncher::saveToFile
 * @brief saves current vector data to file
 * @param path_ path of file
 * @param separator_ string which is used as separator in the csv-file, not used for binary files
 * @param decimalPlaces_ specifies how many decimal places are printed out to the csv-file, not used for binary files
 * @return returns true, if file was sucessfully saved, otherwise false
 *
 * if suffix of path_ is "csv" vector data is saved to a csv-file
 * if suffix of path_ is "" vector data is not save to a file, function returns false
 * if suffix of path_ is not "" and not "csv" vector data is saved to a binary file
 *
 * NOTE : is does not matter, if suffix is uppercase or lower case, or anything in between
 */
bool DataCruncher::saveToFile(const string &path_, char separator_, int decimalPlaces_) const {
    return ( saveToCSVFile(path_,separator_,decimalPlaces_) || saveToBinaryFile(path_) );
}

/**
 * DataCruncher::loadFromCSVFile
 * @brief loads csv-file to the current vector data
 * @param path_ path of file
 * @param separator_ string which is used as separator in the csv-file
 * @return returns true, if file was sucessfully loaded, otherwise false
 */
bool DataCruncher::loadFromCSVFile(const string &path_, char separator_) {
    string suffixOfPath = getSuffixFromString(path_);

    if (suffixOfPath == "CSV") {

        ifstream file;
        string valueAsString;
        vData.clear();

        file.open(path_);
        if (file.is_open()) {

            while(std::getline(file,valueAsString,separator_)) {
                vData.push_back(stod(valueAsString));
            }
            return true;

        } else {
            return false;
        }
    } else {
        return false;
    }
}

/**
 * DataCruncher::saveToCSVFile
 * @brief saves the current VectorData to a csv-file
 * @param path_ path of file
 * @param separator_ string which is used as separator in the csv-file
 * @param decimalPlaces_ specifies how many decimal places are printed out to the csv-file
 * @return returns true, if file was sucessfully saved, otherwise false
 */
bool DataCruncher::saveToCSVFile(const string &path_, char separator_, int decimalPlaces_) const {
    string suffixOfPath = getSuffixFromString(path_);

    if (suffixOfPath == "CSV") {

        ofstream file;
        file.open(path_, ios::trunc);
        if (file.is_open()) {

            file.setf(ios::floatfield,ios::fixed);
            file.precision(decimalPlaces_);
            for (int i = 0; i < vData.getSize(); i++) {
                file << vData[i];
                if (i < vData.getSize() - 1) {
                    file << separator_ << flush;
                }
            }
            file.close();
            return true;

        } else {
            return false;
        }
    } else {
        return false;
    }
}

/**
 * DataCruncher::loadFromBinaryFile
 * @brief loads binary file into current vector data
 * @param path_ path of file
 * @return returns true, if file was sucessfully loaded, otherwise false
 */
bool DataCruncher::loadFromBinaryFile(const string &path_) {
    string suffixOfPath = getSuffixFromString(path_);
    if ( (suffixOfPath != "") && (suffixOfPath != "CSV") ) {
        return true;
    } else {
        return false;
    }
}

/**
 * DataCruncher::saveToBinaryFile
 * @brief saves the current vector data to a binary-file
 * @param path_ path of file
 * @return returns true, if file was sucessfully saved, otherwise false
 */
bool DataCruncher::saveToBinaryFile(const string &path_) const {
    string suffixOfPath = getSuffixFromString(path_);
    if ( (suffixOfPath != "") && (suffixOfPath != "CSV") ) {

        ofstream file;
        file.open(path_, ios::trunc | ios::binary);
        if (file.is_open()) {

            for (int i = 0; i < vData.getSize(); i++) {
                //file << vData[i];
            }
            file << vData[0];
            file.close();
            return true;

        } else {
            return false;
        }

    } else {
        return false;
    }
}

/**
 * DataCruncher::getSuffixFromString
 * @brief extracts the suffix as UPPERCASE from a given string val_
 * @param val_ a string of the structure <filename>.<suffix>
 * @return returns the suffix as UPPERCASE of val_, returns "" if val_ has no suffix
 */
string DataCruncher::getSuffixFromString(const string& val_) const {
    int pos = val_.find_last_of(".");
    if (pos <= 0) {
        return "";
    } else {
        string suffix = val_.substr(pos + 1);
        // transform suffix to uppercase
        transform(suffix.begin(), suffix.end(),suffix.begin(), ::toupper);
        return suffix;
    }
}
