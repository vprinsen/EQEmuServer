/**
 * DO NOT MODIFY THIS FILE
 *
 * This repository was automatically generated and is NOT to be modified directly.
 * Any repository modifications are meant to be made to the repository extending the base.
 * Any modifications to base repositories are to be made by the generator only
 *
 * @generator ./utils/scripts/generators/repository-generator.pl
 * @docs https://eqemu.gitbook.io/server/in-development/developer-area/repositories
 */

#ifndef EQEMU_BASE_ACCOUNT_FLAGS_REPOSITORY_H
#define EQEMU_BASE_ACCOUNT_FLAGS_REPOSITORY_H

#include "../../database.h"
#include "../../strings.h"
#include <ctime>

class BaseAccountFlagsRepository {
public:
	struct AccountFlags {
		int         p_accid;
		std::string p_flag;
		std::string p_value;
	};

	static std::string PrimaryKey()
	{
		return std::string("p_accid");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"p_accid",
			"p_flag",
			"p_value",
		};
	}

	static std::vector<std::string> SelectColumns()
	{
		return {
			"p_accid",
			"p_flag",
			"p_value",
		};
	}

	static std::string ColumnsRaw()
	{
		return std::string(Strings::Implode(", ", Columns()));
	}

	static std::string SelectColumnsRaw()
	{
		return std::string(Strings::Implode(", ", SelectColumns()));
	}

	static std::string TableName()
	{
		return std::string("account_flags");
	}

	static std::string BaseSelect()
	{
		return fmt::format(
			"SELECT {} FROM {}",
			SelectColumnsRaw(),
			TableName()
		);
	}

	static std::string BaseInsert()
	{
		return fmt::format(
			"INSERT INTO {} ({}) ",
			TableName(),
			ColumnsRaw()
		);
	}

	static AccountFlags NewEntity()
	{
		AccountFlags entry{};

		entry.p_accid = 0;
		entry.p_flag  = "";
		entry.p_value = "";

		return entry;
	}

	static AccountFlags GetAccountFlagsEntry(
		const std::vector<AccountFlags> &account_flagss,
		int account_flags_id
	)
	{
		for (auto &account_flags : account_flagss) {
			if (account_flags.p_accid == account_flags_id) {
				return account_flags;
			}
		}

		return NewEntity();
	}

	static AccountFlags FindOne(
		Database& db,
		int account_flags_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE id = {} LIMIT 1",
				BaseSelect(),
				account_flags_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			AccountFlags entry{};

			entry.p_accid = atoi(row[0]);
			entry.p_flag  = row[1] ? row[1] : "";
			entry.p_value = row[2] ? row[2] : "";

			return entry;
		}

		return NewEntity();
	}

	static int DeleteOne(
		Database& db,
		int account_flags_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				account_flags_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		Database& db,
		AccountFlags account_flags_entry
	)
	{
		std::vector<std::string> update_values;

		auto columns = Columns();

		update_values.push_back(columns[0] + " = " + std::to_string(account_flags_entry.p_accid));
		update_values.push_back(columns[1] + " = '" + Strings::Escape(account_flags_entry.p_flag) + "'");
		update_values.push_back(columns[2] + " = '" + Strings::Escape(account_flags_entry.p_value) + "'");

		auto results = db.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				Strings::Implode(", ", update_values),
				PrimaryKey(),
				account_flags_entry.p_accid
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static AccountFlags InsertOne(
		Database& db,
		AccountFlags account_flags_entry
	)
	{
		std::vector<std::string> insert_values;

		insert_values.push_back(std::to_string(account_flags_entry.p_accid));
		insert_values.push_back("'" + Strings::Escape(account_flags_entry.p_flag) + "'");
		insert_values.push_back("'" + Strings::Escape(account_flags_entry.p_value) + "'");

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				Strings::Implode(",", insert_values)
			)
		);

		if (results.Success()) {
			account_flags_entry.p_accid = results.LastInsertedID();
			return account_flags_entry;
		}

		account_flags_entry = NewEntity();

		return account_flags_entry;
	}

	static int InsertMany(
		Database& db,
		std::vector<AccountFlags> account_flags_entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &account_flags_entry: account_flags_entries) {
			std::vector<std::string> insert_values;

			insert_values.push_back(std::to_string(account_flags_entry.p_accid));
			insert_values.push_back("'" + Strings::Escape(account_flags_entry.p_flag) + "'");
			insert_values.push_back("'" + Strings::Escape(account_flags_entry.p_value) + "'");

			insert_chunks.push_back("(" + Strings::Implode(",", insert_values) + ")");
		}

		std::vector<std::string> insert_values;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES {}",
				BaseInsert(),
				Strings::Implode(",", insert_chunks)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static std::vector<AccountFlags> All(Database& db)
	{
		std::vector<AccountFlags> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			AccountFlags entry{};

			entry.p_accid = atoi(row[0]);
			entry.p_flag  = row[1] ? row[1] : "";
			entry.p_value = row[2] ? row[2] : "";

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static std::vector<AccountFlags> GetWhere(Database& db, std::string where_filter)
	{
		std::vector<AccountFlags> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			AccountFlags entry{};

			entry.p_accid = atoi(row[0]);
			entry.p_flag  = row[1] ? row[1] : "";
			entry.p_value = row[2] ? row[2] : "";

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static int DeleteWhere(Database& db, std::string where_filter)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {}",
				TableName(),
				where_filter
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int Truncate(Database& db)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"TRUNCATE TABLE {}",
				TableName()
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

};

#endif //EQEMU_BASE_ACCOUNT_FLAGS_REPOSITORY_H
