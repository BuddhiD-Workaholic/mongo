/**
 *    Copyright (C) 2022-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#include "mongo/db/sorter/sorter_stats.h"

#include "mongo/util/assert_util_core.h"

namespace mongo {
SorterFileStats::SorterFileStats(SorterTracker* sorterTracker) : _sorterTracker(sorterTracker){};

void SorterFileStats::addSpilledDataSize(long long data) {
    if (_sorterTracker) {
        _sorterTracker->bytesSpilled.fetchAndAdd(data);
    }
}

void SorterFileStats::addSpilledDataSizeUncompressed(long long data) {
    if (_sorterTracker) {
        _sorterTracker->bytesSpilledUncompressed.fetchAndAdd(data);
    }
}

SorterStats::SorterStats(SorterTracker* sorterTracker) : _sorterTracker(sorterTracker){};

void SorterStats::incrementSpilledRanges() {
    _spilledRanges++;
    if (_sorterTracker) {
        _sorterTracker->spilledRanges.fetchAndAdd(1);
    }
}

void SorterStats::setSpilledRanges(uint64_t spills) {
    invariant(_spilledRanges == 0);
    _spilledRanges = spills;
    if (_sorterTracker) {
        _sorterTracker->spilledRanges.fetchAndAdd(spills);
    }
}

uint64_t SorterStats::spilledRanges() const {
    return _spilledRanges;
}

void SorterStats::incrementNumSorted(uint64_t sortedKeys) {
    _numSorted += sortedKeys;
    if (_sorterTracker) {
        _sorterTracker->numSorted.fetchAndAdd(sortedKeys);
    }
}

uint64_t SorterStats::numSorted() const {
    return _numSorted;
}

void SorterStats::incrementBytesSorted(uint64_t bytes) {
    _bytesSorted += bytes;
    if (_sorterTracker) {
        _sorterTracker->bytesSorted.fetchAndAdd(bytes);
    }
}

uint64_t SorterStats::bytesSorted() const {
    return _bytesSorted;
}
}  // namespace mongo
