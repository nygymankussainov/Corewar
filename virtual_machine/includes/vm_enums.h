/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_enums.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:38 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/01 13:21:16 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_ENUMS_H
# define VM_ENUMS_H

typedef enum e_operations	t_operations;
typedef enum e_arguments	t_arguments;

enum		t_operations
{
	LIVE	= 0x01,
	LD		= 0x02,
	ST		= 0x03,
	ADD		= 0x04,
	SUB		= 0x05,
	AND		= 0x06,
	OR		= 0x07,
	XOR		= 0x08,
	ZJMP	= 0x09,
	LDI		= 0x0a,
	STI		= 0x0b,
	FORK	= 0x0c,
	LLD		= 0x0d,
	LLDI	= 0x0e,
	LFORK	= 0x0f,
	AFF		= 0x10,
};

enum		t_arguments // maybe it doesn't need
{
	REG		= 0x01,
	DIR		= 0x10,
	IND		= 0x11,
};

#endif

