#pragma once
#include<string>
#include"date.h"
#include<memory>

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);
	bool Evaluate(const Date& date, const string& event) override;

private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& value);
	bool Evaluate(const Date& date, const string& event) override;

private:
	const Comparison cmp_;
	const string value_;

};

class LogicalOperationNode : public Node {
public:

	LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs);
	bool Evaluate(const Date& date, const string& event) override;

private:
	const LogicalOperation operation;
	const shared_ptr<Node> lhs_, rhs_;
};