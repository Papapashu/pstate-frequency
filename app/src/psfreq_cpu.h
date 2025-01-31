/*
 * pstate-frequency Easier control of the Intel p-state driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * For questions please contact pyamsoft at pyam(dot)soft(at)gmail(dot)com
 */

#ifndef CPP_PSFREQ_CPU_H
#define CPP_PSFREQ_CPU_H

#include <string>
#include <vector>

namespace psfreq {

class Cpu {
private:
	class Sysfs {
	private:
		const Cpu &cpu;
		const std::string basePath;
		Sysfs();
	public:
		Sysfs(const Cpu& cpu) :
			cpu(cpu),
			basePath("/sys/devices/system/cpu/")
		{
		}

		~Sysfs()
		{
		}

		bool write(const std::string &path, const std::string &file,
				const std::string &buffer) const;
		bool write(const std::string &path, const std::string &file,
				const int number) const;
		bool write(const std::string &file,
				const std::string &buffer) const;
		bool write(const std::string &file, const int number) const;
		const std::string read(const std::string &file) const;
		const std::string read(const std::string &path,
				const std::string &file) const;
		const std::vector<std::string> readAll(
				const std::string &file) const;
		const std::vector<std::string> readAll(const std::string &path,
				const std::string &file) const;
		const std::vector<std::string> readPipe(const char* command,
				const unsigned int number) const;
	};

	const Sysfs sysfs;
	bool pstate;
	unsigned int number;
	double minInfoFrequency;
	double maxInfoFrequency;
	std::vector<std::string> maxFrequencyFileVector;
	std::vector<std::string> minFrequencyFileVector;
	std::vector<std::string> governorFileVector;
	bool initialized;

	void initializeVector(std::vector<std::string> &vector,
			const std::string what) const;
	double getInfoMinFrequency() const;
	double getInfoMaxFrequency() const;
	unsigned int findNumber() const;
	unsigned int getNumber() const;
	bool findPstate() const;
	double findInfoMinFrequency() const;
	double findInfoMaxFrequency() const;

public:
	Cpu() :
		sysfs(*this),
		pstate(false),
		number(0),
		minInfoFrequency(0),
		maxInfoFrequency(0),
		maxFrequencyFileVector(std::vector<std::string>()),
		minFrequencyFileVector(std::vector<std::string>()),
		governorFileVector(std::vector<std::string>()),
		initialized(false)
	{
	}

	~Cpu()
	{
	}

	bool init();

	int getTurboBoost() const;
	int getInfoMinValue() const;
	int getInfoMaxValue() const;
	int getMinValue() const;
	int getMaxValue() const;
	unsigned int getPowerSupply(const std::string &fullPath) const;
	double getScalingMinFrequency() const;
	double getScalingMaxFrequency() const;
	const std::string getGovernor() const;
	const std::vector<std::string> getRealtimeFrequencies() const;
	const std::vector<std::string> getAvailableGovernors() const;
	const std::string getDriver() const;
	bool hasPstate() const;

	void setScalingMax(const int max) const;
	void setScalingMin(const int min) const;
	void setTurboBoost(const int turbo) const;
	void setGovernor(const std::string &governor) const;

	bool hideDirectory(const std::string &entryName) const;

	static const std::string BAD_READ;
	static const std::string GOVERNOR_INSANE;
	static const std::vector<std::string> BAD_VECTOR;
	static const double INFO_FREQUENCY_INSANE;
	static const double SCALING_FREQUENCY_INSANE;
	static const int PSTATE_VALUE_INSANE;
	static const int TURBO_BOOST_INSANE;
	static const int POWER_SOURCE_AC;
	static const int POWER_SOURCE_BAT;
	static const int POWER_SOURCE_NONE;
	static const unsigned int NO_CPUS;
	static const unsigned int NO_FREQ;
};

}

#endif
