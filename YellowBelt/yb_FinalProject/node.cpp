#include "node.h"

using namespace std;


//EmptyNode
bool EmptyNode::Evaluate(const Date& date, const string& event) { return true; };

//DateComparisonNode
DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date): cmp_(cmp), date_(date) {};

bool DateComparisonNode::Evaluate(const Date& date, const string& event){
	switch (cmp_) {
	case Comparison::Less:
		if (date < date_) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Comparison::LessOrEqual:
		if (date <= date_) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Comparison::Greater:
		if (date > date_) {
			return true;
		}
		else {
			return false;
		}
	case Comparison::GreaterOrEqual:
		if (date >= date_) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Comparison::Equal:
		if (date == date_) {
			return true;
		}
		else{
			return false;
		}
		break;
	case Comparison::NotEqual:
		if (date != date_) {
			return true;
		}
		else {
			return false;
		}
		break;

	}
};

//EventComparisonNode
EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value) : cmp_(cmp), value_(value) {};

bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
	switch (cmp_) {
	case Comparison::Equal:
		if (event == EventComparisonNode::value_) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Comparison::NotEqual:
		if (event != EventComparisonNode::value_) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Comparison::Less:
		if (event < EventComparisonNode::value_) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Comparison::LessOrEqual:
		if (event < EventComparisonNode::value_ || event == EventComparisonNode::value_) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Comparison::Greater:
		if (event > EventComparisonNode::value_) {
			return true;
		}
		else {
			return false;
		}
	case Comparison::GreaterOrEqual:
		if (event > EventComparisonNode::value_ || event == EventComparisonNode::value_) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
};

//LogicalOperationNode
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) :
	operation(op), lhs_(lhs), rhs_(rhs) {};

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
	switch (operation) {
	case LogicalOperation::And:
		if (lhs_->Evaluate(date, event) && rhs_->Evaluate(date, event)) {
			return true;
		}
		else {
			return false;
		}
		break;

	case LogicalOperation::Or:
		if (lhs_->Evaluate(date, event) || rhs_->Evaluate(date, event)) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
};
