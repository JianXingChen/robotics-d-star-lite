/**
 * DStarLite.
 *
 * @package		DStarLite
 * @author		Aaron Zampaglione <azampagl@gmail.com>
 * @copyright	Copyright (C) 2011 Aaron Zampaglione
 * @license		MIT
 */
#ifndef DSTARLITE_PLANNER_H
#define DSTARLITE_PLANNER_H

#include <functional>
#include <algorithm>
#include <list>
#include <map>
#include <unordered_map>
#include "map.h"

using namespace std;
using namespace DStarLite;

namespace DStarLite
{
	class Planner
	{
		public:

			/**
			 * Key compare struct.
			 */
			struct KeyCompare : public binary_function<pair<double,double>, pair<double,double>, bool>
			{
				bool operator()(const pair<double,double>& p1, const pair<double,double>& p2) const;
			};

			/*
			 * @var  static const double  max steps before assuming no path possible
			 */
			static const double MAX_STEPS;

			/**
			 * Constructor.
			 *
			 * @param  Map*    map
			 * @param  Cell*   start
			 * @param  Cell*   goal
			 */
			Planner(Map* map,  Map::Cell* start, Map::Cell* goal);

			/**
			 * Deconstructor.
			 */
			~Planner();

			/**
			 * Returns the generated path.
			 *
			 * @return  list<Map::Cell*>   path
			 */
			list<Map::Cell*> path();

			/**
			 * Gets/Sets a new goal.
			 *
			 * @param   Map::Cell* [optional]   goal
			 * @return  Map::Cell*              new goal
			 */
			Map::Cell* goal(Map::Cell* u = NULL);

			/**
			 * Replans the path.
			 *
			 * @return  bool   solution found
			 */
			bool replan();

			/**
			 * Gets/Sets start.
			 *
			 * @param   Map::Cell* [optional]   new start
			 * @return  Map::Cell*              start
			 */
			Map::Cell* start(Map::Cell* u = NULL);

			/**
			 * Update map.
			 *
			 * @param   Map::Cell*   cell to update
			 * @param   double       new cost of the cell
			 * @return  void
			 */
			void update(Map::Cell* u, double cost);

		protected:			

			/*
			 * @var  list<Map::Cell*>  path
			 */
			list<Map::Cell*> _path;

			/*
			 * @var  double  accumulated heuristic value
			 */
			double _km;

			/*
			 * @var  Map*  map
			 */
			Map* _map;

			/*
			 * @var  Tile*  start, goal, and last start tile
			 */
			Map::Cell* _start;
			Map::Cell* _goal;
			Map::Cell* _last;

			/*
			 * @var  multimap  open list
			 */
			typedef pair<pair<double,double>, Map::Cell*> OL_PAIR;
			typedef multimap<pair<double,double>, Map::Cell*, KeyCompare> OL;
			OL _open_list;

			/*
			 * @var  unordered_map  open hash (stores position in multimap)
			 */
			typedef tr1::unordered_map<Map::Cell*, OL::iterator, Map::Cell::Hash> OH;
			OH _open_hash;

			/*
			 * @var  unordered_map  cell hash (keeps track of all the cells)
			 */
			typedef tr1::unordered_map<Map::Cell*, pair<double,double>, Map::Cell::Hash> CH;
			CH _cell_hash;

			/**
			 * Generate cell.
			 *
			 * @param   Map::Cell*
			 * @return  void
			 */
			void _cell(Map::Cell* u);

			/**
			 * Compute shortest path.
			 *
			 * @return  bool   successful
			 */
			bool _compute();

			/**
			 * Calculatse the cost from one cell to another cell.
			 * 
			 * @param   Map::Cell*   cell a
			 * @param   Map::Cell*   cell b
			 * @return  double       cost between a and b
			 */
			double _cost(Map::Cell* a, Map::Cell* b);

			/**
			 * Gets/Sets g value for a cell.
			 * 
			 * @param   Map::Cell*          cell to retrieve/update
			 * @param   double [optional]   new g value
			 * @return  double              g value 
			 */
			double _g(Map::Cell* u, double value = DBL_MIN);

			/**
			 * Calculates heuristic between two cells.
			 *
			 * @param   Map::Cell*   cell a
			 * @param   Map::Cell*   cell b
			 * @return  double       heuristic value
			 */
			double _h(Map::Cell* a, Map::Cell* b);

			/**
			 * Calculates key value for cell.
			 *
			 * @param   Map::Cell*            cell to calculate for
			 * @return  pair<double,double>   key value
			 */
			pair<double,double> _k(Map::Cell* u);

			/**
			 * Inserts cell into open list.
			 *
			 * @param   Map::Cell*            cell to insert
			 * @param   pair<double,double>   key vakue for the cell
			 * @return  void
			 */
			void _list_insert(Map::Cell* u, pair<double,double> k);

			/**
			 * Removes cell from the open list.
			 *
			 * @param   Map::Cell*   cell to remove
			 * @return  void
			 */
			void _list_remove(Map::Cell* u);

			/**
			 * Gets/Sets rhs value for a cell.
			 * 
			 * @param   Map::Cell*          cell to retrieve/update
			 * @param   double [optional]   new rhs value
			 * @return  double              rhs value
			 */
			double _rhs(Map::Cell* u, double value = DBL_MIN);

			/**
			 * Updates cell.
			 *
			 * @param   Map::Cell*   cell to update
			 * @return  void
			 */
			void _update(Map::Cell* u);
	};
};


#endif // DSTARLITE_PLANNER_H