/* Copyright (C) 
 * 2016 - John Torres <Schecterwolfe@gmail.com>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

#ifndef _CONFIGSECTOR_H
#define _CONFIGSECTOR_H

#include <map>
#include <string>
#include <vector>

/**
 * Container for a log sector, which themselves have mutiple options and fields
 */
class ConfigSector
{
    public:
        enum SectorIndex
        {
            IndexSectorName = 0,

            IndexCount
        };

        ConfigSector();
        ConfigSector(const std::string &strSecName);
        virtual ~ConfigSector();

        void setSectorName(const std::string &strSecName);
        const std::string &getSectorName() const;

        void addOption(const std::string &strOption, const std::string &strVal);
        bool removeOption(const std::string &strOption);
        std::string &getValue(const std::string &strOption);
        std::string &getIndexValue(int iIndex);
        const std::map<std::string, std::string> &getOptionValues() const;
        bool parseSector(const std::string &strSector, unsigned int *puiOffset = nullptr);
        std::string serializeSector() const;

    private:
        std::string strSecName;
        std::string strStaticEmpty;
        std::map<std::string, std::string> mapOptionToValue;

        void skipFileComment(const std::string &strSector, size_t *puiOffset = nullptr) const;
};

#endif
