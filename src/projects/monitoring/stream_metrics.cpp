//
// Created by getroot on 20. 1. 16.
//

#include "stream_metrics.h"
#include "application_metrics.h"

namespace mon
{
		// Getter
		uint32_t StreamMetrics::GetOriginRequestTimeMSec()
        {
            return _request_time_to_origin_msec;
        }
		uint32_t StreamMetrics::GetOriginResponseTimeMSec()
        {
            return _response_time_from_origin_msec;
        }

		uint64_t StreamMetrics::GetTotalBytesIn()
        {
            return _total_bytes_in.load();
        }
		uint64_t StreamMetrics::GetTotalBytesOut()
        {
            return _total_bytes_out;
        }
		uint32_t StreamMetrics::GetTotalConnections()
        {
            return _total_connections;
        }

        uint32_t StreamMetrics::GetMaxTotalConnections()
        {
            return _max_total_connections;
        }
		std::chrono::system_clock::time_point StreamMetrics::GetMaxTotalConnectionsTime()
        {
            return _max_total_connection_time;
        }

		uint64_t StreamMetrics::GetBytesOut(PublisherType type)
        {
            return _publisher_metrics[static_cast<int8_t>(type)]._bytes_out;
        }
		uint64_t StreamMetrics::GetConnections(PublisherType type)
        {
            return _publisher_metrics[static_cast<int8_t>(type)]._connections;
        }

		// Setter
		void StreamMetrics::SetOriginRequestTimeMSec(uint32_t value)
        {
            _request_time_to_origin_msec = value;
            UpdateDate();
        }
		void StreamMetrics::SetOriginResponseTimeMSet(uint32_t value)
        {
            _response_time_from_origin_msec = value;
            UpdateDate();
        }

		void StreamMetrics::IncreaseBytesIn(uint64_t value)
        {
            _total_bytes_in += value;
            UpdateDate();
        }
		void StreamMetrics::IncreaseBytesOut(PublisherType type, uint64_t value)
        {
            _publisher_metrics[static_cast<int8_t>(type)]._bytes_out += value;
            _total_bytes_out += value;
            UpdateDate();
        }
		
		void StreamMetrics::OnSessionConnected(PublisherType type)
        {
            _publisher_metrics[static_cast<int8_t>(type)]._connections ++;
            _total_connections ++;
            if(_total_connections > _max_total_connections)
            {
                _max_total_connections.exchange(_total_connections);
                _max_total_connection_time = std::chrono::system_clock::now();
            }
            UpdateDate();
        }
		void StreamMetrics::OnSessionDisconnected(PublisherType type)
        {
            _publisher_metrics[static_cast<int8_t>(type)]._connections --;
            _total_connections --;
            UpdateDate();
        }
}