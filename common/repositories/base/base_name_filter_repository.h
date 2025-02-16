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

#ifndef EQEMU_BASE_NAME_FILTER_REPOSITORY_H
#define EQEMU_BASE_NAME_FILTER_REPOSITORY_H

#include "../../database.h"
#include "../../strings.h"
#include <ctime>

class BaseNameFilterRepository {
public:
	struct NameFilter {
		int         id;
		std::string name;
	};

	static std::string PrimaryKey()
	{
		return std::string("id");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"id",
			"name",
		};
	}

	static std::vector<std::string> SelectColumns()
	{
		return {
			"id",
			"name",
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
		return std::string("name_filter");
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

	static NameFilter NewEntity()
	{
		NameFilter entry{};

		entry.id   = 0;
		entry.name = "";

		return entry;
	}

	static NameFilter GetNameFilterEntry(
		const std::vector<NameFilter> &name_filters,
		int name_filter_id
	)
	{
		for (auto &name_filter : name_filters) {
			if (name_filter.id == name_filter_id) {
				return name_filter;
			}
		}

		return NewEntity();
	}

	static NameFilter FindOne(
		Database& db,
		int name_filter_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE id = {} LIMIT 1",
				BaseSelect(),
				name_filter_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			NameFilter entry{};

			entry.id   = atoi(row[0]);
			entry.name = row[1] ? row[1] : "";

			return entry;
		}

		return NewEntity();
	}

	static int DeleteOne(
		Database& db,
		int name_filter_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				name_filter_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		Database& db,
		NameFilter name_filter_entry
	)
	{
		std::vector<std::string> update_values;

		auto columns = Columns();

		update_values.push_back(columns[1] + " = '" + Strings::Escape(name_filter_entry.name) + "'");

		auto results = db.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				Strings::Implode(", ", update_values),
				PrimaryKey(),
				name_filter_entry.id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static NameFilter InsertOne(
		Database& db,
		NameFilter name_filter_entry
	)
	{
		std::vector<std::string> insert_values;

		insert_values.push_back(std::to_string(name_filter_entry.id));
		insert_values.push_back("'" + Strings::Escape(name_filter_entry.name) + "'");

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				Strings::Implode(",", insert_values)
			)
		);

		if (results.Success()) {
			name_filter_entry.id = results.LastInsertedID();
			return name_filter_entry;
		}

		name_filter_entry = NewEntity();

		return name_filter_entry;
	}

	static int InsertMany(
		Database& db,
		std::vector<NameFilter> name_filter_entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &name_filter_entry: name_filter_entries) {
			std::vector<std::string> insert_values;

			insert_values.push_back(std::to_string(name_filter_entry.id));
			insert_values.push_back("'" + Strings::Escape(name_filter_entry.name) + "'");

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

	static std::vector<NameFilter> All(Database& db)
	{
		std::vector<NameFilter> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			NameFilter entry{};

			entry.id   = atoi(row[0]);
			entry.name = row[1] ? row[1] : "";

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static std::vector<NameFilter> GetWhere(Database& db, std::string where_filter)
	{
		std::vector<NameFilter> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			NameFilter entry{};

			entry.id   = atoi(row[0]);
			entry.name = row[1] ? row[1] : "";

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

#endif //EQEMU_BASE_NAME_FILTER_REPOSITORY_H
