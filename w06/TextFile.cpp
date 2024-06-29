/*/////////////////////////////////////////////////////////////////////////
                        Assignment 6 - Milestone 1
Full Name  : Chia-Yu Chien
Student ID#: 157049222
Email      : cchien8@myseneca.ca
Section    : NCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#include "TextFile.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;
namespace seneca {
   Line::operator const char* () const {
      return (const char*)m_value;
   }
   Line& Line::operator=(const char* lineValue) {
      delete[] m_value;
      m_value = new char[strlen(lineValue) + 1];
      strcpy(m_value, lineValue);
      return *this;
   }
   Line::~Line() {
      delete[] m_value;
   }

   bool TextFile::isValid() const{
      return m_filename != nullptr;
   }
   
   bool TextFile::isEmpty() const{
      return m_filename == nullptr && m_textLines == nullptr && m_noOfLines == 0;
   }

   void TextFile::setEmpty(){
      delete []m_textLines;
      m_textLines = nullptr;

      delete []m_filename;
      m_filename = nullptr;

      m_noOfLines = 0;
   }

   void TextFile::setFilename(const char*fname, bool isCopy) {
      if(fname == nullptr) {
         return;
      }

      if(m_filename != nullptr){
         delete[]m_filename;
      }
      
      if(!isCopy){
         m_filename = new char[strlen(fname) + 1];
         strcpy(m_filename, fname);
      }else{
         m_filename = new char[strlen(fname) + 3]; // allocate extra two spaces for "abc.txt" to "C_abc.txt" 
         m_filename[0] = 'C';
         m_filename[1] = '_';
         strcpy(m_filename+2, fname);
      }
   }

   void TextFile::setNoOfLines() {
      if(m_filename == nullptr) {
         return;
      }

      m_noOfLines = 0;

      ifstream fin;
      fin.open(m_filename);
      if(fin.is_open()) {
         char ch;
         while(fin.get(ch)) {
            if(ch == '\n'){
               m_noOfLines++;
            }
         }
         fin.close();
      }

      if(m_noOfLines != 0){
         // increase m_noOfLines by one, just in case, the last line does not have a new line at the end
         m_noOfLines++;
      } else{
         delete []m_filename;
         m_filename = nullptr;
      }

   }

   void TextFile::loadText() {
      if(m_filename == nullptr) {
         return;
      }

      if(m_textLines != nullptr){
         delete [] m_textLines;
      }

      m_textLines = new Line[m_noOfLines];
      ifstream fin;
      fin.open(m_filename);
      if(fin.is_open()) {
         string line;
         int lineCount = 0;
         while(getline(fin, line)) {
            m_textLines[lineCount] = line.c_str();
            lineCount ++;
         }
         m_noOfLines = lineCount;
         fin.close();
      }
   }

   void TextFile::saveAs(const char *fileName)const {
      if(fileName == nullptr) {
         return;
      }

      ofstream fon;
      fon.open(fileName);
      if(fon.is_open()){
         for(unsigned int i = 0; i < m_noOfLines; i++) {
            fon << m_textLines[i] << "\n";
         }
         fon.close();
      }
   }

   TextFile::TextFile(unsigned pageSize) {
      m_textLines = nullptr;
      m_filename = nullptr;
      m_noOfLines = 0;
      m_pageSize = pageSize;
   }

   TextFile::TextFile(const char* filename, unsigned pageSize) {
      m_textLines = nullptr;
      m_filename = nullptr;
      m_noOfLines = 0;
      m_pageSize = pageSize;
      setFilename(filename);
      setNoOfLines();
      loadText();

   }

   TextFile::TextFile(const TextFile& tf) {
      m_textLines = nullptr;
      m_filename = nullptr;
      m_noOfLines = 0;
      m_pageSize = tf.m_pageSize;

      if(tf.isValid()){
         // Sets the file-name to the name of the incoming TextFile object (isCopy set to true)
         setFilename(tf.m_filename, true);

         //Saves the content of the incoming TextFile under the file name of the current TextFile
         tf.saveAs(m_filename);
         
         // set the number of lines
         m_noOfLines = tf.m_noOfLines;

         // loads the Text
         loadText();
      }
   }

   TextFile& TextFile::operator=(const TextFile& tf) {
      if(tf.isValid()) {
         // deallocate the dynamic array of Text and sets the pointer to null
         delete []m_textLines;
         m_textLines = nullptr;

         // Saves the content of the incoming TextFile under the current filename
         tf.saveAs(m_filename);

         // Sets the number of lines
         m_noOfLines = tf.m_noOfLines;

         // loads the Text
         loadText();
      }
      
      return *this;
   }

   TextFile::~TextFile(){
      delete []m_textLines;
      m_textLines = nullptr;

      delete []m_filename;
      m_filename = nullptr;
   }

   unsigned TextFile::lines()const{
      return m_noOfLines;
   }

   std::ostream& TextFile::view(std::ostream& ostr)const {
      if(isEmpty()) {
         return cout;
      }

      cout << m_filename << "\n";
      cout << "==========\n";

      unsigned int currline = 0;
      while(currline < m_noOfLines){
         cout << m_textLines[currline] << "\n";
         currline++;
         
         // pauses after printing "m_pageSize" lines and prompts the user Hit ENTER 
         // to continue... and waits for the user to press enter and repeats until all lines are printed.
         if(currline % m_pageSize == 0) {
            cout << "Hit ENTER to continue...";
            bool entered = false;
            while(!entered){
               char ch = cin.get();
               if(ch == '\n') {
                  entered = true;
                  break;
               }
            }
         }
      }

      return cout;
   }

   std::istream& TextFile::getFile(std::istream& istr){
      string fname;
      istr >> fname;
      clearInputBuffer();
      setFilename(fname.c_str());
      setNoOfLines();
      loadText();

      return istr;
   }
   
   const char* TextFile::operator[](unsigned index)const {
      if(isEmpty()) {
         return nullptr;
      }

      index %= m_noOfLines;
      return m_textLines[index];
   }

   TextFile::operator bool()const {
      // Returns true if the TextFile is not in an empty state and returns false if it is.
      return !isEmpty();
   }

   const char* TextFile::name()const{
      return m_filename;
   }

   std::ostream& operator<<(std::ostream& ostr, const TextFile& text){
      text.view(ostr);
      return ostr;
   }

   std::istream& operator>>(std::istream& istr, TextFile& text){
      text.getFile(istr);
      return istr;
   }

   void clearInputBuffer(void)
   {
     while (cin.get() != '\n') ;
   }
}