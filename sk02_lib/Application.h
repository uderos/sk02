#pragma once
class Application
{
public:
	Application();
	virtual ~Application();

	void Run(const std::string & input_file_name);

private:

	void run_exec(const std::string & input_file_name);

};

