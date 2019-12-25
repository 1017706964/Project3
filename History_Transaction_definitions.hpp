#ifndef _HISTORY_TRANSACTION_HPP_
#define _HISTORY_TRANSACTION_HPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project3.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK
//
 Transaction::Transaction(std::string ticker_symbol, unsigned int day_date,
	 unsigned int month_date, unsigned year_date,
	 bool buy_sell_trans, unsigned int number_shares,
	 double trans_amount) {
	 symbol = ticker_symbol;
	 day = day_date;
	 month = month_date;
	 year = year_date;
	if (buy_sell_trans){
		trans_type = "Buy";
	}else{
		trans_type = "Sell";
	}
	 shares = number_shares;
	 amount = trans_amount;
	 p_next = nullptr;
	 trans_id=assigned_trans_id;
     ++assigned_trans_id;
	 acb=0;
	 acb_per_share=0;
	 share_balance=0;
	 cgl=0;
 } 

// Destructor
// TASK
//
 Transaction::~Transaction()
 {

 }

// TASK
// Overloaded < operator.
//
 bool Transaction::operator < (Transaction const& other)
 {
if (year <= other.year && month<=other.month && day <= other.day)
{
	return true;
}
else {
	return false;
	}
}
// GIVEN
// Member functions to get values. 
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values. 
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " " 
    << std::setw(4) << get_symbol() << " " 
    << std::setw(4) << get_day() << " "  
    << std::setw(4) << get_month() << " " 
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) { 
    std::cout << "  Buy  "; 
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " " 
    << std::setw(10) << get_amount() << " " 
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl() 
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK
//

History::History()
{
	p_head = nullptr;
}

// Destructor
// TASK
//
History::~History()
{
	while (p_head != nullptr)
	{
		Transaction* current_head{ p_head };
		p_head = p_head->get_next();
		delete current_head;
		current_head = nullptr;
	}
	
}

// TASK
// read_transaction(...): Read the transaction history from file. 
//
void History:: read_history() {
	ece150::open_file();
	while (ece150::next_trans_entry()) {
		//std::cout << "read" << std::endl;
		Transaction* op {new Transaction(ece150::get_trans_symbol(),  ece150::get_trans_day(),
	 ece150::get_trans_month(), ece150::get_trans_year(),
	ece150::get_trans_type(), ece150::get_trans_shares(),
	 ece150::get_trans_amount())};
	insert(op);
	 	//std::cout << 7;
	// 	 	Transaction* up {new Transaction(ece150::get_trans_symbol(),  ece150::get_trans_day(),
	//  ece150::get_trans_month(), ece150::get_trans_year(),
	// ece150::get_trans_type(), ece150::get_trans_shares(),
	//  ece150::get_trans_amount())};
	//  	 	std::cout << 8;

	}
	ece150::close_file();

}

// insert(...): Insert transaction into linked list.
//
void History::insert(Transaction* p_new_trans)
{
	if (p_head == nullptr) {
		p_head = p_new_trans;
	}
	else {
		Transaction *tail = p_head;
		while (tail-> get_next() != nullptr)
		{
			tail = tail->get_next();
		}
		tail-> set_next (p_new_trans) ;
	}
}

// TASK
// sort_by_date(): Sort the linked list by trade date.
//

/*void History::sort_by_date() {
	read_history();
	Transaction* new_head { p_head };
	while (p_head->get_next()!=nullptr) {
		p_head = p_head->get_next();
		while (new_head < p_head)
		{
			p_head->set_next(p_head);
			p_head = new_head;
		}
		delete new_head;
		new_head = nullptr;
} }*/


// TASK
// update_acb_cgl(): Updates the ACB and CGL values. 
//
/*
void History::update_acb_cgl(){
	Transaction* new_p_head {nullptr};
	Transaction* new_head {p_head};
	//new_head = get_p_head() -> get_next();
	//new_p_head=get_p_head();
	while (new_head != nullptr){
		if (new_p_head -> get_trans_type()){
		new_head -> set_acb(new_p_head -> get_acb() + new_head-> get_amount());
		new_head -> set_share_balance(new_p_head->get_share_balance()+new_head ->get_shares());
		}else{
		new_head ->  set_acb(new_head -> get_acb() - new_p_head-> get_acb_per_share()*new_head -> get_shares());
		new_head -> set_share_balance(new_head->get_share_balance() - new_p_head ->get_shares());
		new_head -> set_cgl(new_head->get_amount()-new_p_head -> get_acb_per_share ()* new_head -> get_shares());
		}
		new_head -> set_acb_per_share (new_head->get_acb()/new_head->get_shares());
		new_p_head = new_p_head ->get_next();
		new_head = new_head -> get_next();
	}
}
*/
void History::update_acb_cgl()
{
	Transaction* entry{p_head};
	Transaction* last_entry{nullptr};
	unsigned int share_balance{0};
	double acb {0};
	while (entry!=nullptr)
	{

		if (entry->get_trans_type())
		{
			entry->set_share_balance( share_balance+entry->get_shares() );
			entry->set_acb( acb+entry->get_amount());
			entry->set_cgl(0.0);
		}else{
			entry->set_share_balance( share_balance-entry->get_shares() );
			entry->set_acb( acb-(entry->get_shares()*(last_entry->get_acb_per_share())));
			entry->set_cgl(entry->get_amount()-(entry->get_shares()*last_entry->get_acb_per_share()));
		}
		entry->set_acb_per_share( entry->get_acb()/entry->get_share_balance() );
		acb=entry->get_acb();
		last_entry=entry;
		share_balance=entry->get_share_balance();
		entry = entry->get_next();
	}
}


// TASK
// compute_cgl(): )Compute the ACB, and CGL.
//
double History::compute_cgl(unsigned int year){
	Transaction* p_new_head {p_head};
	double year_cgl{0};
	while(p_new_head != nullptr){
		if (p_new_head -> get_year() == year )
		{
			year_cgl = p_new_head -> get_cgl() + p_new_head -> get_next() -> get_cgl();
		}
		p_new_head = p_new_head -> get_next();
	}
	return year_cgl;
}

// TASK
// print() Print the transaction history.
//

void History::print(){
	std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
	Transaction* new_head {p_head};
	while(new_head!=nullptr)
	{
		new_head -> print();
		new_head = new_head -> get_next();
		//std::cout << 6;
	}
	std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
// 
Transaction *History::get_p_head() { return p_head; }


#endif

