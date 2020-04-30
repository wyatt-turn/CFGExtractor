
#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"

#pragma once


class Grammar
{

    private:


       //Element which is either a rule or Terminal of the grammar.
        struct element
        {
            std::string value; 
            bool isTerminal = true;
            bool isTerminalRule =  false;                  //used for some semantic checking
            bool genTerminals = false;                     //whether a nonTerminal generates terminals
            std::vector< std::vector <element*> > rhsList = {};        //list of right hand sides, each rhs will be indexes of elements in Grammar's universe
            
            //First and follow sets used to tell if grammar has predictive parser
            std::vector<element*> FIRST = {};
            std::vector<element*> FOLLOW  = {};

        };

        std::vector<element*> universe;              //every terminal/rule element is stored here (including $ and epsilon)
        bool isAmbigious;
        bool predictiveParser;

        Lexer* lexer;

        //std::vector<Token>;

        /*
            parser methods, implemented in parser.cpp
        */
        void parse_grammar();
        void parse_rules();
        void parse_ruleSection();
        void parse_ruleList();
        void parse_rule();
        std::vector< std::vector<element*>> parse_rhsList();
        std::vector<element*> parse_rhs();
        std::vector<element*>* parse_rhs(std::vector<element*>*); //overloaded to handle recursive case easier
        void parse_terminalRules();
        void parse_terminal_ruleList();
        void parse_terminal_rule();
        std::vector< std::vector<element*> > parse_terminal_rhsList();
        std::vector<element*> parse_terminal_rhs();
        void syntax_error(int);
        Token expect_token(TokenType);
        Token peek_token();
        element* elementLookup(std::string);
        void combineRHS(std::vector< std::vector<element*>>*, 
                        std::vector< std::vector<element*>> *);
        void terminalCheck();
        void terminalRHSCheck(std::vector< std::vector<element*> >*);


        /*
            
        */
        element* getElement(int);
        void printRHS(std::vector< std::vector<element*>>*);


        void removeUselessSyms();
        void getGenSymbols();
        void getReachableSyms();
        void iniGenSyms();
        void iniReachSyms();

    public:

        void parse();
        void printSymbols();
        void printRules();
        Grammar();


};