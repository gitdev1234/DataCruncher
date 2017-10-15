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
 * @return returns either total number of elements successfully read, or negative error code
 *
 * if suffix of path_ is "csv", file is interpreted as a csv-file
 * if suffix of path_ is "", vector data is not loaded, function returns -3
 * if suffix of path_ is not "" and not "csv" file is interpreted as binary file
 *
 * NOTE : is does not matter, if suffix is uppercase or lower case, or anything in between
 *
 * possible return values :
 * return value > 0   --> total number of elements successfully read
 * return value = 0   --> error : error because of empty vData
 * return value = -2  --> error : could not open file
 * return value = -3  --> error : wrong suffix of path
 */
int DataCruncher::loadFromFile(const string &path_, char separator_) {
    int result = loadFromCSVFile(path_,separator_);

    // if loading from csv produced an error, try to read from binary file
    if (result <= 0) {
        result = loadFromBinaryFile(path_);
    }

    // exit
    return result;
}

/**
 * DataCruncher::saveToFile
 * @brief saves current vector data to file
 * @param path_ path of file
 * @param separator_ string which is used as separator in the csv-file, not used for binary files
 * @param decimalPlaces_ specifies how many decimal places are printed out to the csv-file, not used for binary files
 * @return returns either total number of elements successfully written, or negative error code
 *
 * if suffix of path_ is "csv", vector data is saved to a csv-file
 * if suffix of path_ is "" vector data is not save to a file, function returns -3
 * if suffix of path_ is not "" and not "csv" vector data is saved to a binary file
 *
 * NOTE : is does not matter, if suffix is uppercase or lower case, or anything in between
 *
 * possible return values :
 * return value > 0   --> total number of elements successfully written
 * return value = 0   --> error : error because of empty vData
 * return value = -2  --> error : could not open file
 * return value = -3  --> error : wrong suffix of path
 */
int DataCruncher::saveToFile(const string &path_, char separator_, int decimalPlaces_) const {
    int result = saveToCSVFile(path_,separator_,decimalPlaces_);

    // if saving to csv produced an error, try to save to binary file
    if (result <= 0)  {
        result = saveToBinaryFile(path_);
    }

    // exit
    return result;
}

/**
 * DataCruncher::loadFromCSVFile
 * @brief loads csv-file to the current vector data
 * @param path_ path of file
 * @param separator_ string which is used as separator in the csv-file
 * @return returns either total number of elements successfully read, or negative error code
 *
 * possible return values :
 * return value > 0   --> total number of elements successfully read
 * return value = 0   --> error : error because of empty vData
 * return value = -2  --> error : could not open file
 * return value = -3  --> error : wrong suffix of path
 */
int DataCruncher::loadFromCSVFile(const string &path_, char separator_) {
    int result = 0;

    string suffixOfPath = getSuffixFromString(path_);
    if (suffixOfPath == "CSV") {

        ifstream file;
        string valueAsString;
        vData.clear();

        // open filestream in textmode
        file.open(path_);

        // opened file successfully
        if (file.is_open()) {

            // iterate file and push values into vData
            while(std::getline(file,valueAsString,separator_)) {
                vData.push_back(stod(valueAsString));
            }

            result = vData.getSize();

        } else {
            result = -2;
        }
    } else {
        result = -3;
    }

    // exit
    return result;
}

/**
 * DataCruncher::saveToCSVFile
 * @brief saves the current VectorData to a csv-file
 * @param path_ path of file
 * @param separator_ string which is used as separator in the csv-file
 * @param decimalPlaces_ specifies how many decimal places are printed out to the csv-file
 * @return returns either total number of elements successfully written, or negative error code
 *
 * possible return values :
 * return value > 0   --> total number of elements successfully written
 * return value = 0   --> error : error because of empty vData
 * return value = -2  --> error : could not open file
 * return value = -3  --> error : wrong suffix of path
 */
int DataCruncher::saveToCSVFile(const string &path_, char separator_, int decimalPlaces_) const {
    int result = 0;

    string suffixOfPath = getSuffixFromString(path_);
    if (suffixOfPath == "CSV") {

        // open filestream in textmode
        ofstream file;
        file.open(path_, ios::trunc);

        // opened file successfully
        if (file.is_open()) {

            // define how to print double values
            file.setf(ios::floatfield,ios::fixed);
            file.precision(decimalPlaces_);

            // iterate vData and print out values seperated by "seperator"
            for (int i = 0; i < vData.getSize(); i++) {
                file << vData[i];
                if (i < vData.getSize() - 1) {
                    file << separator_ << flush;
                }
            }

            result = vData.getSize();

        } else {
            result = -2;
        }

        // close file
        file.close();

    } else {
        result = -3;
    }

    // exit
    return result;
}

/**
 * DataCruncher::loadFromBinaryFile
 * @brief loads binary file into current vector data
 * @param path_ path of file
 * @return returns either total number of elements successfully read, or negative error code
 *
 * possible return values :
 * return value > 0   --> total number of elements successfully read
 * return value = 0   --> error : error while reading file
 * return value = -1  --> error : size of file does not fit with size of vData (vector<double>)
 * return value = -2  --> error : could not open file
 * return value = -3  --> error : wrong suffix of path
 */
int DataCruncher::loadFromBinaryFile(const string &path_) {
    int result = 0;

    string suffixOfPath = getSuffixFromString(path_);
    if ( (suffixOfPath != "") && (suffixOfPath != "CSV") ) {

        // open filestream in rb (read, binary) mode
        FILE* file;
        file = fopen(path_.c_str(),"rb");

        // opened file successfully
        if (file != NULL) {

            // obtain file size
            fseek(file , 0 , SEEK_END);
            long sizeInBytes = ftell (file);
            rewind(file);

            // check file size
            unsigned int sizeOfElement = sizeof(vData[0]);
            unsigned int numberOfElements = sizeInBytes / sizeOfElement;
            if ( (sizeInBytes % sizeOfElement == 0) &&
                 (numberOfElements > 0) ) {

                // adjust size of vData to size of file
                vData.resize(numberOfElements);

                // read "numberOfElements" blocks with a size of "sizeOfElement"
                // bytes each from the filestream "file" into vData starting
                // at the address of the first element of vData
                double* startAddressOfData = &vData[0];
                result = fread(startAddressOfData,sizeOfElement,numberOfElements,file);

            } else {
               result = -1;
            }
        } else {
            result = -2;
        }

        // close filestream
        fclose(file);

    } else {
        result = -3;
    }

    // exit
    return result;
}

/**
 * DataCruncher::saveToBinaryFile
 * @brief saves the current vector data to a binary-file
 * @param path_ path of file
 * @return returns either total number of elements successfully written, or negative error code
 *
 * possible return values :
 * return value > 0   --> total number of elements successfully written
 * return value = 0   --> error : error while reading file
 * return value = -2  --> error : could not open file
 * return value = -3  --> error : wrong suffix of path
 */
int DataCruncher::saveToBinaryFile(const string &path_) const {
    int result = 0;

    string suffixOfPath = getSuffixFromString(path_);
    if ( (suffixOfPath != "") && (suffixOfPath != "CSV") ) {

        // create / open filestream in wb (write, binary) mode
        FILE* file;
        file = fopen(path_.c_str(),"wb");

        // created / opened file successfully
        if (file != NULL) {

            // start at the address of the first element of vData and
            // write "numberOfElements" blocks with a size of "sizeOfElement"
            // bytes each into the filestream "file"
            const double* startAddressOfData = &vData[0];
            unsigned int numberOfElements = vData.getSize();
            unsigned int sizeOfElement = sizeof(vData[0]);
            result = fwrite(startAddressOfData,sizeOfElement,numberOfElements,file);

        } else {
            result = -2;
        }

        // close filestream
        fclose(file);

    } else {
        result = -3;
    }

    // exit
    return result;
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


/* --- getters / setters --- */

bool DataCruncher::getStatisticValuesAreUpToDate() const {
    return statisticValuesAreUpToDate;
}

void DataCruncher::setStatisticValuesAreUpToDate(bool statisticValuesAreUpToDate_) {
    statisticValuesAreUpToDate = statisticValuesAreUpToDate_;
}

double DataCruncher::getVariance() const {
    return variance;
}

void DataCruncher::setVariance(double variance_) {
    variance = variance_;
}

double DataCruncher::getStdDeviation() const {
    return stdDeviation;
}

void DataCruncher::setStdDeviation(double stdDeviation_) {
    stdDeviation = stdDeviation_;
}

double DataCruncher::getMedian() const {
    return median;
}

void DataCruncher::setMedian(double median_) {
    median = median_;
}

double DataCruncher::getAverage() const {
    return average;
}

void DataCruncher::setAverage(double average_) {
    average = average_;
}

/* --- analyze --- */

// statistic values

/**
 * @brief DataCruncher::calcAverage
 * @return
 */
double DataCruncher::calcAverage() const {
    double average = 0;
    for ( int pos = 0; pos < vData.getSize(); pos++) {
        average += vData[pos];
    }

    return (double) average/(double) vData.size();
}

double DataCruncher::calcMedian() const {
    return 0;
}

double DataCruncher::calcStdDeviation() const {
    return 0;
}

double DataCruncher::calcVariance() const {
    return 0;
}

double DataCruncher::calcHistogramm() const {
    return 0;
}

void DataCruncher::calcAllStatisticValues() {
    setAverage(calcAverage());
    setMedian(calcMedian());
    setStdDeviation(calcStdDeviation());
    setVariance(calcVariance());
    setStatisticValuesAreUpToDate(true);
}

/* --- modify --- */
/**
 * @brief DataCruncher::removeErrors
 * @param changeLocalVectorData_
 * @return
 */
VectorData DataCruncher::removeErrors(bool changeLocalVectorData_) {
    if (changeLocalVectorData_) {
        // todo
        setStatisticValuesAreUpToDate(false);
    } else {

    }
}

/**
 * DataCruncher::zTransform
 * @brief z-transforms the data of vData
 * @param changeLocalVectorData_ false if this function has to work on a copy of vData, true if it works on the member vData
 * @return returns an VectorData-object with the values of vData after a z-transformation
 * This function z-Transforms the data within vData. After the z-transformation the data
 * has an average of 0 and an variance of 1.
 * The z-transformation can get used to standardize data of different scales. This makes the data more comparable.
 *
 * Please note : If changeLocalVectorData_ = true (default value) this function modifies the data within the local member variable
 * vData of this class. If changeLocalVectorData_ = false the returned value is a copy of the local member variable vData.
 * In this case vData is not modified.
 */
VectorData DataCruncher::zTransform(bool changeLocalVectorData_) {
    VectorData *result;
    VectorData newVData;

    // calc average and standard deviation if necessary
    if (! getStatisticValuesAreUpToDate()) {
        setAverage(this->calcAverage());
        setStdDeviation(this->calcStdDeviation());
    }

    // if zTransform has to change local vectorData
    // result will point to this.vData
    // if not, it will point to a new created copy of this.vData
    if (changeLocalVectorData_) {
        result = &vData;  // this is no copy
        setStatisticValuesAreUpToDate(false);
    } else {
        newVData = vData; // this is a copy
        result = &newVData;
    }

    // z-transform(x) = (x - average) / stdDeviation
    *result -= getAverage();
    if (stdDeviation != 0) {
        *result /= getStdDeviation();
    }

    return *result;

}

/**
 * DataCruncher::undoZTransform
 * @brief undos the z-transformation of vData
 * @param averageBeforeZ_ average value of vData before z-transformation
 * @param stdDeviationBeforeZ_ standard deviation value of vData before z-transformation
 * @param changeLocalVectorData_ false if this function has to work on a copy of vData, true if it works on the member vData
 * @return returns an VectorData-object with original values before z-transformation
 *
 * Please note : If changeLocalVectorData_ = true (default value) this function modifies the data within the local member variable
 * vData of this class. If changeLocalVectorData_ = false the returned value is a copy of the local member variable vData.
 * In this case vData is not modified.
 */
VectorData DataCruncher::undoZTransform(double averageBeforeZ_, double stdDeviationBeforeZ_, bool changeLocalVectorData_) {
    VectorData *result;
    VectorData newVData;

    // if zTransform has to change local vectorData
    // result will point to this.vData
    // if not, it will point to a new created copy of this.vData
    if (changeLocalVectorData_) {
        result = &vData;  // this is no copy
        setStatisticValuesAreUpToDate(false);
    } else {
        newVData = vData; // this is a copy
        result = &newVData;
    }

    // z-transform(x) = (x - average) / stdDeviation
    // --> x(z-transform) = (z-transform * stdDeviation) + average
    *result *= stdDeviationBeforeZ_;
    *result += averageBeforeZ_;

    return *result;

}

/**
 * @brief DataCruncher::differentiate
 * @param changeLocalVectorData_
 * @return
 */
VectorData DataCruncher::differentiate(bool changeLocalVectorData_) {
    if (changeLocalVectorData_) {
        // todo
        setStatisticValuesAreUpToDate(false);
    } else {

    }
}

/**
 * @brief DataCruncher::integrate
 * @param changeLocalVectorData_
 * @return
 */
VectorData DataCruncher::integrate(bool changeLocalVectorData_) {
    if (changeLocalVectorData_) {
        // todo
        setStatisticValuesAreUpToDate(false);
    } else {

    }
}

/**
 * @brief DataCruncher::movingAverageFiltering
 * @param changeLocalVectorData_
 * @return
 */
VectorData DataCruncher::movingAverageFiltering(bool changeLocalVectorData_) {
    if (changeLocalVectorData_) {
        // todo
        setStatisticValuesAreUpToDate(false);
    } else {

    }
}
