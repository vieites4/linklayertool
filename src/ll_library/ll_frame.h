/*
 * @file ll_frame.h
 * @author Ricardo Tubío (rtpardavila[at]gmail.com)
 * @version 0.1
 *
 * @section LICENSE
 *
 * This file is part of linklayertool.
 * linklayertool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * linklayertool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with linklayertool.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef LL_FRAME_H_
#define LL_FRAME_H_

#include "execution_codes.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/if_ether.h>

//#define KERNEL_RING 1

#ifdef KERNEL_RING
	#include <linux/if_packet.h>
#endif

/***************************************************************** DATA TYPES */

typedef struct ethhdr eth_header_t;		/*!< Data type definition for ethhdr. */

/*!
	\struct ieee8023_buffer
	\brief Structure for decoding an IEEE 802.3 ethernet frame.
 */
typedef struct ieee8023_buffer
{

	eth_header_t header;		/*!< Header of the ethernet frame. */
	char data[ETH_DATA_LEN];	/*!< Data of the ethernet frame. */

} ieee8023_buffer_t;

#define LEN__IEEE8023_BUFFER sizeof(ieee8023_buffer_t)

/*!
	\struct ieee8023_frame
	\brief Structure for managing an IEEE 802.3 ethernet frame.
 */
typedef struct ieee8023_frame
{

	int frame_len;				/*!< Length of the total bytes read. */

	ieee8023_buffer_t frame;	/*!< Buffer with the frame. */

} ieee8023_frame_t;

#define LEN__IEEE8023_FRAME sizeof(ieee8023_frame_t)

/****************************************************************** FUNCTIONS */

/*!
	\brief Allocates memory for an ethhdr structure, including MAX PAYLOAD.
	\return A pointer to the newly allocated block of memory.
*/
struct ethhdr *new_ethhdr();

/*!
	\brief Allocates memory for a ieee8023_buffer structure.
	\return A pointer to the newly allocated block of memory.
*/
ieee8023_buffer_t *new_ieee8023_buffer();

/*!
	\brief Allocates memory for a ieee8023_frame structure.
	\return A pointer to the newly allocated block of memory.
*/
ieee8023_frame_t *new_ieee8023_frame();

/*!
	\brief Prints the given IEEE 802.3 frame.
	\param frame The IEEE 802.3 frame to be printed.
 */
void print_ieee8023_frame(const ieee8023_frame_t *frame);

/*!
	\brief Reads from a socket an IEEE 802.3 frame.
	\param socket_fd The socket from where to read the frame.
	\return A pointer to the frame.
 */
#ifdef KERNEL_RING
	int read_ieee8023_frame(const void *rx_ring, ieee8023_frame_t *rx_frame);
#else
	int read_ieee8023_frame(const int socket_fd, ieee8023_frame_t *rx_frame);
#endif

#define BYTES_PER_LINE 8	/*!< Number of bytes per line to be printed. */

/*!
	\brief Prints the data field of the given IEEE 802.3 frame.
	\param frame The IEEE 802.3 frame whose data is to be printed.
 */
void print_eth_data(const ieee8023_frame_t *frame);

/*!
	\brief Prints the given ethernet address.
	\param eth_address Ethernet address as an array.
 */
void print_eth_address(const unsigned char *eth_address);

#endif /* LL_FRAME_H */