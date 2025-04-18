/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _WORKERTHREAD_H
#define _WORKERTHREAD_H

#include "Define.h"
#include <atomic>
#include <thread>

template <typename T>
class ProducerConsumerQueue;

class MySQLConnection;
class SQLOperation;

class AC_DATABASE_API DatabaseWorker
{
public:
    DatabaseWorker(ProducerConsumerQueue<SQLOperation*>* newQueue, MySQLConnection* connection);
    ~DatabaseWorker();

private:
    ProducerConsumerQueue<SQLOperation*>* _queue;
    MySQLConnection* _connection;

    void WorkerThread();
    std::thread _workerThread;

    DatabaseWorker(DatabaseWorker const& right) = delete;
    DatabaseWorker& operator=(DatabaseWorker const& right) = delete;
};

#endif
