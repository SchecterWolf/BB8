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

#ifndef _BB8_LOG_H
#define _BB8_LOG_H

#include "LogManager.h"

/**
 * Simple macros for logging once the loggers have already been set up
 */

#define _INTERNAL_BB8_LOG(_logLevel, _logCategory, ret, _format, _args...) \
            LogManager::gtLog.log(LogContext(_logLevel, LogCategory::_logCategory, __FILE__, __LINE__), _format, ## _args) \

#define logCritical(_logCategory, _format, _args...) _INTERNAL_BB8_LOG(LogLevel::Critical, _logCategory, false, _format, ## _args)
#define logError(_logCategory, _format, _args...) _INTERNAL_BB8_LOG(LogLevel::Error, _logCategory, false, _format, ## _args)
#define logWarn(_logCategory, _format, _args...) _INTERNAL_BB8_LOG(LogLevel::Warn, _logCategory, true, _format, ## _args)
#define logInfo(_logCategory, _format, _args...) _INTERNAL_BB8_LOG(LogLevel::Info, _logCategory, true, _format, ## _args)
#define logDebug(_logCategory, _format, _args...) _INTERNAL_BB8_LOG(LogLevel::Debug, _logCategory, true, _format, ## _args)

#endif
