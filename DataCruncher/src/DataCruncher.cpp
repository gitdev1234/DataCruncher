/**
 * DataCruncher.cpp
 * Purpose: implements class DataCruncher
 *
 * @author Wall.Of.Death
 * @version 2.2
 */

#include "DataCruncher.h"

/* --- load / save --- */



/**
 * DataCruncher::saveToFile
 * @brief saves current vector data to file
 * @param path_ path of file
 * @return returns true, if file was sucessfully saved, otherwise false
 *
 * if suffix of path_ is "csv" vector data is saved to a csv-file
 * if suffix of path_ is "" vector data is not save to a file, function returns false
 * if suffix of path_ is not "" and not "csv" vector data is saved to a binary file
 */
bool DataCruncher::saveToFile(const string &path_) const {
    return ( saveToCSVFile(path_) || saveToBinaryFile(path_) );
}

/**
 * DataCruncher::saveToCSVFile
 * @brief saves the current VectorData to a csv-file
 * @param path_ path of file
 * @return returns true, if file was sucessfully saved, otherwise false
 */
bool DataCruncher::saveToCSVFile(const string &path_) const {
    string suffixOfPath = getSuffixFromString(path_);
    if (suffixOfPath == "CSV")  {
        return true;
    } else {
        return false;
    }
}

/**
 * DataCruncher::saveToBinaryFile
 * @brief saves the current VectorData to a binary-file
 * @param path_ path of file
 * @return returns true, if file was sucessfully saved, otherwise false
 */
bool DataCruncher::saveToBinaryFile(const string &path_) const {
    string suffixOfPath = getSuffixFromString(path_);
    if ( (suffixOfPath != "") && (suffixOfPath != "CSV") ) {
        return true;
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
