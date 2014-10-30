/*
 * @file botTemplate.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-04
 * Template for users to create their own bots
 */

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include<stdlib.h>
#include<stdio.h>

using namespace std;
using namespace Desdemona;
int recurse_minimax(Desdemona::OthelloBoard&,Desdemona::OthelloBoard&, Desdemona::Turn, Desdemona::Turn, int, int,int);
float evaluate(OthelloBoard&,OthelloBoard&,Turn );


class MyBot: public OthelloPlayer
{
	public:
		/**
		 * Initialisation routines here
		 * This could do anything from open up a cache of "best moves" to
		 * spawning a background processing thread. 
		 */
		MyBot( Turn turn );

		/**
		 * Play something 
		 */
		virtual Move play( const OthelloBoard& board );
	private:
};

	MyBot::MyBot( Turn turn )
: OthelloPlayer( turn )
{
}

Move MyBot::play( const OthelloBoard& board )
{
//	cout << "play start9"<< endl;
	//system("clear");
//	system("sleep 1");
	system("tput setaf 3");
	cout << "MyBot" << endl;
	board.print();
	system("reset=\"$(tput sgr0)\"");
	list<Move> moves = board.getValidMoves( turn );
	
	list<Move>::iterator it;
	list<Move>::iterator required;

	//cout << board.getValidMoves( turn ) << endl;
	//cout << "play start1"<< endl;

	OthelloBoard SampleBoard = board;
	OthelloBoard CurrentBoard =board;

	Turn currentturn;

	currentturn=turn;
	//cout << "play start2"<< endl;
	int blackcount=SampleBoard.getBlackCount();
		int redcount=SampleBoard.getRedCount();
	Move requiredmove = *moves.begin();
	//cout << "play start3"<< endl;
	int i=1;
	int alpha = -99999;
	int beta = 99999;
	int best = -999;
	cout << "moves size "<<moves.size()<<endl;
	int depth = 5;
	if( moves.size() >=15)
		{
		depth = 4;
		}
	if( moves.size() <= 5)
			{
			depth = 6;
			}
	//cout << "play start"<< endl;
	for(it=moves.begin(); it!=moves.end() ; it++,i++)
	{
		
		SampleBoard.makeMove(turn,(*it).x,(*it).y);
		//if ((blackcount + redcount) > 45)
			//depth =5;
		int val=recurse_minimax(CurrentBoard,SampleBoard,turn,currentturn,depth,alpha,beta);
		//cout << "in up"<<endl;
		if(val > alpha)
			alpha = val;
		if(alpha > best)
		{
			best = alpha;
			requiredmove = *it;
		}
		blackcount=SampleBoard.getBlackCount();
		redcount=SampleBoard.getRedCount();
		//int value = evaluate(it);
	
		SampleBoard = CurrentBoard;

	}
//	cout << "top list over"<<endl;
//	cout << (requiredmove).x<<(requiredmove).y<<endl;
	//time(&endtimer);
	//cout << "hello" <<endl;
	//cout <<(endtimer - starttimer)<<endl;
	return requiredmove;
}


     

int  recurse_minimax(OthelloBoard &actualboard,OthelloBoard &board,Turn turn,Turn currentturn,int depth,int alpha,int beta)
{
	list<Move> moves = board.getValidMoves( turn );
	OthelloBoard dummy=board;
	int evaluate_value;
	list<Move>::iterator it;
	if(depth == 0 )
	{
		//cout << "inleaf"<<endl;
	 evaluate_value=evaluate(actualboard,board,currentturn);
	 //cout << "outleaf"<<endl;
		return evaluate_value;
	}
	
	else if(turn == currentturn)
	{
		
	for(it=moves.begin(); it!=moves.end() ; it++)
		{
		//cout << "in max"<<endl;
		int val;
		board.makeMove(turn,(*it).x,(*it).y);
		//cout << "before node"<<endl;
		if(turn == RED)
				val= recurse_minimax(actualboard,board,BLACK,currentturn,depth-1,alpha,beta);
				else
				val=	 recurse_minimax(actualboard,board,RED,currentturn,depth-1,alpha,beta);
		//cout << "after node"<<endl;
		
		if ((val > alpha)) {
		                alpha = val;
		               
		            }
		            if (alpha >= beta) {
		                break;
		            }
		
		
		
		
		
		board = dummy;
		}
	//cout << "list1 over"<<endl;
	    return alpha;
	}
	
	else
	{
		int maxvalue = 99999;
		//cout << "in min"<<endl;
		for(it=moves.begin(); it!=moves.end() ; it++)
				{
			float val;
				board.makeMove(turn,(*it).x,(*it).y);
			//	cout << "before node2"<<endl;
				if(turn == RED)
						val= recurse_minimax(actualboard,board,BLACK,currentturn,depth-1,alpha,beta);
						else
							val= recurse_minimax(actualboard,board,RED,currentturn,depth-1,alpha,beta);
				//cout << "after node2"<<endl;
				//maxvalue=(val < maxvalue )? val : maxvalue;
				
				if ((val < beta)) {
				                beta = val;
				               
				            }
				            if (beta <= alpha) {
				                break;
				            }
				
				board = dummy;
				}
//		cout << "list2 over"<<endl;
		return beta;
		
		
		
	}
}




float evaluate(OthelloBoard &actualboard,OthelloBoard &board,Turn turn)
{
	int blackcount=board.getBlackCount();
	int redcount=board.getRedCount();
	int actualblackcount=actualboard.getBlackCount();
		int actualredcount=actualboard.getRedCount();
		blackcount -= actualblackcount;
		redcount -= actualredcount;
	list<Move> moves = board.getValidMoves( turn );
	Turn oppturn;
	oppturn=(turn == BLACK)? RED : BLACK;
	list<Move> oppmoves = board.getValidMoves( oppturn );
	int positionvalue=0;
	//cout << board[0][0]<<"hell"<<endl;
	
	
	//cout << "hell1"<<endl;
	//cout << "corner start eval"<<endl;
	
if(board.get(0,0) == turn && actualboard.get(0,0) != turn )
					positionvalue+=10;
if(board.get(0,7) == turn && actualboard.get(0,7) != turn )
					positionvalue+=10;
if(board.get(7,0) == turn && actualboard.get(7,0) != turn )
					positionvalue+=10;
if(board.get(7,7) == turn && actualboard.get(7,7) != turn )
					positionvalue+=10;

if(  board.get(1,1)==turn && actualboard.get(1,1) != turn )
					positionvalue=positionvalue-20;
if(  board.get(6,6)==turn  && actualboard.get(6,6) != turn)
					positionvalue=positionvalue-20;
if(  board.get(1,6)==turn  && actualboard.get(1,6) != turn )
					positionvalue=positionvalue-20;
if(  board.get(6,1)==turn && actualboard.get(6,1) != turn)
					positionvalue=positionvalue-20;
if(board.get(0,1)==turn ||board.get(1,0)==turn || board.get(6,7)==turn ||  board.get(7,6)==turn ||   board.get(0,6)==turn || board.get(1,7)==turn ||  board.get(7,1)==turn || board.get(6,0)==turn )
	positionvalue =positionvalue - 20;
//cout << "corner end eval"<<endl;
				
//cout << "hell2"<<endl;
	if(blackcount + redcount < 50)
		{
			
			
				if(turn == BLACK)
						return (((blackcount - redcount)/100.0) + (positionvalue) + moves.size()-oppmoves.size());
						else
							return (((redcount - blackcount)/100.0) + (positionvalue) + moves.size()-oppmoves.size());
		}
	//cout << "first"<<endl;
	//if(blackcount + redcount >= 35)
	//{
		if(turn == BLACK)
		return ((blackcount - redcount)*5);
		else
			return ((redcount - blackcount)*5);
	//}
	//cout << "second return"<<endl;
	//cout << "hell3"<<endl;
		
		//return ((positionvalue-oppmoves.size())*5);
		
	
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
	OthelloPlayer* createBot( Turn turn )
	{
		return new MyBot( turn );
	}

	void destroyBot( OthelloPlayer* bot )
	{
		delete bot;
	}
}


